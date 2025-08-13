#pragma once
#include "raylib.h"
#include <deque>
#include <vector>

// Pipe class represents a single pipe obstacle in the Flappy Bird game.
class Pipe
{
private:
    // Window dimensions and offset for pipe placement
    int win_w{640}, win_h{480}, win_offset{64};

    // Texture for the pipe, loaded from file
    Texture2D texture{LoadTexture("sprites/pipe-green.png")};

    // Position of the pipe (x, y)
    Vector2 pipePos{static_cast<float>(win_w), static_cast<float>(GetRandomValue(250, 450))};

    // Flag to indicate if the player has passed this pipe
    bool isPassed{};

public:
    /**
     * @brief Default constructor for Pipe.
     * Initializes a pipe with default window size, texture, and random vertical position.
     */
    Pipe() {};

    /**
     * @brief Constructs a Pipe with a given position.
     * @param pos The position to initialize the pipe at.
     */
    Pipe(Vector2 pos);

    /**
     * @brief Constructs a Pipe with a given texture and position.
     * @param tex The texture to use for the pipe.
     * @param pos The position to initialize the pipe at.
     */
    Pipe(Texture2D tex, Vector2 pos);

    /**
     * @brief Gets the position of the pipe.
     * @return Reference to the pipe's position vector.
     */
    Vector2 &getPos();

    /**
     * @brief Gets the texture of the pipe.
     * @return The Texture2D object representing the pipe's texture.
     */
    Texture2D getTexture();

    /**
     * @brief Gets the width of the pipe.
     * @return The width of the pipe in pixels.
     */
    int getWidth();

    /**
     * @brief Gets the height of the pipe.
     * @return The height of the pipe in pixels.
     */
    int getHeight();

    /**
     * @brief Gets the collision rectangle for the upper pipe.
     * Used for collision detection with the player.
     * @return Rectangle representing the upper pipe's collision area.
     */
    Rectangle getUpperCollisionRec();

    /**
     * @brief Gets the collision rectangle for the bottom pipe.
     * Used for collision detection with the player.
     * @return Rectangle representing the bottom pipe's collision area.
     */
    Rectangle getBottomCollisionRec();

    /**
     * @brief Sets whether the pipe has been passed by the player.
     * Used for scoring logic.
     * @param passVal True if the pipe has been passed, false otherwise.
     */
    void setIsPassed(bool passVal) { isPassed = passVal; };

    /**
     * @brief Checks if the pipe has been passed by the player.
     * Used for scoring logic.
     * @return True if the pipe has been passed, false otherwise.
     */
    bool getIsPassed() { return isPassed; };
};