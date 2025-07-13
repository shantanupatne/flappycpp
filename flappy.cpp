#include <iostream>
#include "raylib.h"

bool InAir(Vector2 pos, int win_h, Texture2D flappy) {
    return pos.y < win_h;
}

int main() {
    const int win_w{640}, win_h{480}, gravity{3000}, win_offset{64};

    InitWindow(win_w, win_h + 2 * win_offset, "Template");
    SetTargetFPS(20);
    float birdScale{1.5f};

    Texture2D midflap {LoadTexture("sprites/bluebird-midflap.png")};
    Texture2D downflap {LoadTexture("sprites/bluebird-downflap.png")};
    Texture2D upflap {LoadTexture("sprites/bluebird-upflap.png")};
    Texture2D flappy {midflap};
    
    Vector2 birdPos{win_w / 3.f, (win_h / 3.f) + win_offset};
    DrawTextureEx(flappy, birdPos, 0.f, birdScale, WHITE);
    int velocity{};
    int gameState{}; // 0 = playing, 1 = paused, 2 = over
    int score{};
    while (!WindowShouldClose()){
        float dT = GetFrameTime();
        BeginDrawing();
        ClearBackground(WHITE);
        DrawRectangle(0.f, 0.f, win_w, win_offset, WHITE);
        DrawText("Flappy Bird", 10, 10, 40, BLACK);
        DrawText(TextFormat("%i", score), 10, win_h + win_offset + 10, 40, BLACK);

        if (gameState > 1 && IsKeyPressed(KEY_SPACE)) {
            gameState = 0;
            birdPos = {win_w / 3.f, (win_h / 3.f) + win_offset};
            score = -1;
        }

        if (!InAir(birdPos, win_h, flappy)) {
            DrawRectangle(0.f, win_offset, win_w, win_h, Color{0, 0, 0, 128});
            DrawText("Game Over!", 10, 2 * win_h / 3, 40, BLACK);
            DrawText("Press [Space] to restart.", 10, 2 * win_h / 3 + 40, 20, BLACK);
            EndDrawing();
            gameState = 2;
            continue;
        }
        velocity += InAir(birdPos, win_h, flappy) ? gravity * dT: 0;

        flappy = InAir(birdPos, win_h, flappy) ? upflap : midflap;
        if (IsKeyPressed(KEY_SPACE) && velocity >= gravity / 12.5f) {
            velocity = -gravity / 4.0f;
            flappy = downflap;
            score ++;
        }
        std::cout<<velocity<<std::endl;
        birdPos.y += velocity * dT;
        DrawTextureEx(flappy, birdPos, 0.f, birdScale, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
