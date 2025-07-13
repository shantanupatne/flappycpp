#include <iostream>
#include "raylib.h"

const int win_w{640}, win_h{480}, gravity{3000}, win_offset{64};
bool InAir(Vector2 pos, Texture2D flappy)
{
    return pos.y < (win_h + win_offset);
}

Vector2 scrollBackground(Texture2D texture, float scale, Vector2 pos, float velX, float dT)
{
    pos.x -= velX * dT;
    if (pos.x <= -(texture.width * scale))
    {
        pos.x = 0;
    }
    Vector2 bg1Pos{pos};
    Vector2 bg2Pos{pos.x + scale * texture.width, pos.y};
    Vector2 bg3Pos{pos.x + 2 * scale * texture.width, pos.y};
    DrawTextureEx(texture, bg1Pos, 0., scale, WHITE);
    DrawTextureEx(texture, bg2Pos, 0., scale, WHITE);
    DrawTextureEx(texture, bg3Pos, 0., scale, WHITE);

    return pos;
}

int main()
{

    InitWindow(win_w, win_h + 2 * win_offset, "Template");
    SetTargetFPS(20);
    float birdScale{1.5f}, bgScale{1.1f};

    Texture2D midflap{LoadTexture("sprites/bluebird-midflap.png")};
    Texture2D downflap{LoadTexture("sprites/bluebird-downflap.png")};
    Texture2D upflap{LoadTexture("sprites/bluebird-upflap.png")};
    Texture2D flappy{midflap};

    Texture2D base{LoadTexture("sprites/base.png")};
    Texture2D background{LoadTexture("sprites/background-day.png")};

    Vector2 birdPos{win_w / 4.f, (win_h / 3.f) + win_offset};
    DrawTextureEx(flappy, birdPos, 0.f, birdScale, WHITE);
    int velocity{};
    int gameState{}; // 0 = playing, 1 = paused, 2 = over
    int score{};

    Vector2 basePos{0.f, (float)(win_h + 2 * win_offset - base.height)};

    Vector2 bgPos{};
    while (!WindowShouldClose())
    {
        float dT = GetFrameTime();
        BeginDrawing();
        ClearBackground(WHITE);
        
        bgPos = scrollBackground(background, bgScale, bgPos, 20, dT);
        basePos = scrollBackground(base, bgScale, basePos, 60, dT);


        DrawRectangle(0.f, 0.f, win_w, win_offset, WHITE);
        DrawLineEx({0, win_offset - 2}, {win_w, win_offset - 2}, 4, BLACK);
        DrawText("Flappy Bird", 10, 10, 40, BLACK);
        DrawText(TextFormat("%i", score), win_w - 50, 10, 40, BLACK);

        if (gameState > 1 && IsKeyPressed(KEY_SPACE))
        {
            gameState = 0;
            birdPos = {win_w / 4.f, (win_h / 3.f) + win_offset};
            score = -1;
        }

        if (!InAir(birdPos, flappy) || birdPos.y < -100 )
        {
            DrawRectangle(0.f, win_offset, win_w, win_h + win_offset, Color{255, 255, 255, 128});
            DrawText("Game Over!", 10, 2 * win_h / 3, 40, BLACK);
            DrawText(TextFormat("Score: %i", score), 10, 2 * win_h / 3 + 40, 40, BLACK);
            DrawText("Press [Space] to restart.", 10, 2 * win_h / 3 + 80, 20, BLACK);
            EndDrawing();
            gameState = 2;
            continue;
        }

        velocity += InAir(birdPos, flappy) ? gravity * dT : 0;

        flappy = InAir(birdPos, flappy) ? upflap : midflap;
        if (IsKeyPressed(KEY_SPACE) && velocity >= gravity / 12.5f)
        {
            velocity = -gravity / 4.0f;
            flappy = downflap;
            score++;
        }
        birdPos.y += velocity * dT;
        DrawTextureEx(flappy, birdPos, 0.f, birdScale, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
