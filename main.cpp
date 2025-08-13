/**
 * @author Shantanu Patne
 * @date July 12, 2025
 * @brief Simple Flappy Bird Game
 */

#include <iostream>
#include <deque>
#include <vector>
#include "raylib.h"
#include "pipe.h"
#include "flappy.h"
#include "global.h"

/**
 * @brief Scrolls and draws a repeating background texture.
 *
 * This function updates the horizontal position of a background texture to create a scrolling effect.
 * It draws three instances of the texture side by side to ensure seamless looping as the background scrolls.
 *
 * @param texture The Texture2D object representing the background image.
 * @param scale The scaling factor to apply to the texture when drawing.
 * @param pos The current position (Vector2) of the background.
 * @param velX The horizontal scrolling speed (pixels per second).
 * @param dT The delta time (in seconds) since the last frame.
 * @return Vector2 The updated position of the background after scrolling.
 */
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

/**
 * @brief Scrolls and manages the pipes in the Flappy Bird game.
 *
 * This function updates the horizontal position of each pipe in the provided deque,
 * simulating the scrolling effect as the game progresses. When a pipe moves off-screen
 * to the left, it is repositioned to the right of the last pipe with a new random vertical
 * position, creating an endless loop of pipes. The function also handles drawing the pipes
 * within the visible vertical range and resets the "passed" state for recycled pipes.
 *
 * @param pipes         Reference to a deque of Pipe objects to be scrolled and managed.
 * @param pipeInterval  The horizontal distance between consecutive pipes.
 * @param velX          The horizontal velocity at which pipes move (pixels per second).
 * @param dT            The time delta since the last update (in seconds).
 */
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

    if (!pipesToMove.empty() && !pipes.empty()) 
    {
        for (auto pipeIndex : pipesToMove)
        {
            Pipe pipe = pipes[pipeIndex];
            pipe.setIsPassed(false);
            pipes.pop_front();
            pipes.push_back(pipe);
        }
    }
}

/**
 * @brief Generates and appends a series of Pipe objects to the provided deque.
 *
 * This function creates MAX_PIPES number of Pipe objects, each positioned horizontally
 * at intervals of pipeInterval starting from the right edge of the window (win_w).
 * The vertical position of each pipe is randomized between 250 and 450.
 *
 * @param pipes Reference to a deque of Pipe objects where the generated pipes will be appended.
 * @param pipeInterval The horizontal distance between consecutive pipes.
 */
void GeneratePipes(std::deque<Pipe> &pipes, float pipeInterval)
{
    for (int i = 0; i < MAX_PIPES; i++)
    {
        pipes.push_back(Pipe{Vector2{win_w + i * pipeInterval, (float)GetRandomValue(250, 450)}});
    }
}


/**
 * @brief Entry point for the Flappy Bird game.
 *
 * Initializes the game window, loads textures, and manages the main game loop.
 * Handles game states (playing, paused, game over), user input, rendering, and game logic such as
 * background scrolling, pipe generation and movement, collision detection, scoring, and restarting the game.
 *
 */
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
                    // passed the pipe
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
