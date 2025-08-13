#include <iostream>
#include <deque>
#include <vector>
#include "raylib.h"
#include "pipe.h"
#include "flappy.h"
#include "global.h"

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

void moveToBack(std::deque<Pipe> &pipes)
{
    Pipe pipe = pipes[0];
    pipe.setIsPassed(false);
    pipes.pop_front();
    pipes.push_back(pipe);
}

void scrollPipe(std::deque<Pipe> &pipes, float pipeInterval, float velX, float dT)
{
    std::vector<size_t> pipesToMove;
    for (size_t i = 0; i < pipes.size(); ++i)
    {
        Pipe &pipe = pipes[i];
        pipe.getPos().x -= velX * dT;
        if (pipe.getPos().x < -pipe.getWidth() - 10)
        {
            Pipe lastPipe = pipes.back();
            pipe.getPos().x = lastPipe.getPos().x + pipeInterval;
            pipe.getPos().y = GetRandomValue(250, 500);
            pipesToMove.push_back(i);
        }

        // Only draw pipes that are within the visible vertical range (y < 500)
        if (pipe.getPos().y < 500)
        {
            DrawTexturePro(pipe.getTexture(), {0.f, 0.f, 1.f * pipe.getWidth(), 1.f * pipe.getHeight()}, {pipe.getPos().x, pipe.getPos().y, 1.f * pipe.getWidth(), 1.f * pipe.getHeight()}, {0.f, 0.f}, 0.f, WHITE);
            DrawTexturePro(pipe.getTexture(), {0.f, 0.f, 1.f * pipe.getWidth(), -1.f * pipe.getHeight()}, {pipe.getPos().x, pipe.getPos().y - 150.f, 1.f * pipe.getWidth(), 1.f * pipe.getHeight()}, {0.f, 1.f * pipe.getHeight()}, 0.f, WHITE);
        }
    }
    for (size_t i = 0; i < pipesToMove.size(); ++i)
    {
        if (!pipes.empty())
        {
            moveToBack(pipes);
        }
    }
}

void GeneratePipes(std::deque<Pipe> &pipes, float pipeInterval)
{
    for (int i = 0; i < MAX_PIPES; i++)
    {
        pipes.push_back(Pipe{Vector2{win_w + i * pipeInterval, (float)GetRandomValue(250, 450)}});
    }
}

int main()
{

    InitWindow(win_w, win_h + 2 * win_offset, "Flappy Bird");
    SetTargetFPS(60);
    float bgScale{1.1f};

    Flappy flappy;

    Texture2D base{LoadTexture("sprites/base.png")};
    Texture2D background{LoadTexture("sprites/background-day.png")};

    int gameState{}; // 0 = playing, 1 = paused, 2 = over
    int score{};

    Vector2 basePos{0.f, (float)(win_h + 2 * win_offset - base.height)};
    Vector2 bgPos{};

    float pipeInterval{win_w / 3.f};

    std::deque<Pipe> pipes;
    GeneratePipes(pipes, pipeInterval);

    int scrollVel{60};
    while (!WindowShouldClose())
    {
        float dT = GetFrameTime();
        BeginDrawing();
        ClearBackground(WHITE);

        bgPos = scrollBackground(background, bgScale, bgPos, scrollVel / 3, dT);
        scrollPipe(pipes, pipeInterval, scrollVel, dT);
        basePos = scrollBackground(base, bgScale, basePos, scrollVel, dT);

        if (gameState == 2)
        {
            DrawRectangle(0.f, win_offset, win_w, win_h + win_offset, Color{255, 255, 255, 128});
            DrawText("Game Over!", 10, 2 * win_h / 3, 40, BLACK);
            DrawText(TextFormat("Score: %i", score), 10, 2 * win_h / 3 + 40, 40, BLACK);
            DrawText("Press [Space] to restart.", 10, 2 * win_h / 3 + 80, 20, BLACK);
            if (IsKeyPressed(KEY_SPACE))
            {
                gameState = 0;
                score = 0;
                scrollVel = 60;
                pipes.clear();
                flappy.Reset();
                GeneratePipes(pipes, pipeInterval);
                continue;
            }
        }
        else
        {
            if (!flappy.CheckInAir() || flappy.GetPos().y < -100)
            {
                gameState = 2;
                scrollVel = 0;
                // velocity = 0.f;
                continue;
            }

            flappy.Update(dT, IsKeyPressed((KEY_SPACE)));

            Rectangle birdRec{flappy.GetCollisionRect()};
            for (auto &pipe : pipes)
            {
                // Check for collision
                Rectangle bottomPipeRec{ pipe.getBottomCollisionRec() };
                if (CheckCollisionRecs(birdRec, bottomPipeRec) || CheckCollisionRecs(birdRec, pipe.getUpperCollisionRec()))
                {
                    // collision
                    gameState = 2;
                    scrollVel = 0;
                    break;
                }
                // Check if bird is across the pipe and increment score.
                if (((bottomPipeRec.x + bottomPipeRec.width) < birdRec.x) && !pipe.getIsPassed())
                {
                    score += 1;
                    pipe.setIsPassed(true);
                }
            }
            flappy.Draw();
        }

        DrawRectangle(0.f, 0.f, win_w, win_offset, WHITE);
        DrawLineEx({0, win_offset - 2}, {win_w, win_offset - 2}, 4, BLACK);
        DrawText("Flappy Bird", 10, 10, 40, BLACK);
        DrawText(TextFormat("%i", score), win_w - 60, 10, 40, BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
