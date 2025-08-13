#pragma once
#include "raylib.h"
#include "global.h"

/**
 * @class Flappy
 * @brief Represents the player-controlled bird in the Flappy Bird game.
 *
 * Handles the bird's position, animation, physics, rendering, and collision detection.
 */
class Flappy
{
public:
    /**
     * @brief Default constructor. Initializes the bird with default values.
     */
    Flappy() {};

    /**
     * @brief Constructs the bird at a specific starting position.
     * @param startPos The initial position of the bird.
     */
    Flappy(Vector2 startPos) : pos(startPos) {};

    /**
     * @brief Constructs the bird with specific textures, position, and scale.
     * @param mid Texture for mid-flap animation.
     * @param up Texture for upward-flap animation.
     * @param down Texture for downward-flap animation.
     * @param startPos The initial position of the bird.
     * @param scale The scale factor for rendering the bird.
     */
    Flappy(Texture2D mid, Texture2D up, Texture2D down, Vector2 startPos, float scale)
        : midflap(mid), downflap(down), upflap(up), pos(startPos), birdScale(scale) {};

    /**
     * @brief Updates the bird's state, including position and animation.
     * @param dT Delta time since last update.
     * @param jumpPressed Whether the jump input is currently pressed.
     */
    void Update(float dT, bool jumpPressed);

    /**
     * @brief Draws the bird on the screen.
     */
    void Draw();

    /**
     * @brief Gets the collision rectangle for the bird.
     * @return Rectangle representing the bird's collision bounds.
     */
    Rectangle GetCollisionRect() const;

    /**
     * @brief Gets the current position of the bird.
     * @return The bird's position as a Vector2.
     */
    Vector2 GetPos() { return pos; };

    /**
     * @brief Resets the bird to its initial state.
     */
    void Reset();

    /**
     * @brief Checks if the bird is currently in the air.
     * @return True if the bird is in the air, false otherwise.
     */
    bool CheckInAir() { return InAir(pos, flappy); };

private:
    // Texture for the bird's mid-flap animation frame
    Texture2D midflap{LoadTexture("sprites/bluebird-midflap.png")};
    // Texture for the bird's downward-flap animation frame
    Texture2D downflap{LoadTexture("sprites/bluebird-downflap.png")};
    // Texture for the bird's upward-flap animation frame
    Texture2D upflap{LoadTexture("sprites/bluebird-upflap.png")};
    // Currently displayed texture (changes based on animation state)
    Texture2D flappy{midflap};
    // Current position of the bird on the screen
    Vector2 pos{win_w / 4.f, (win_h / 3.f) + win_offset};
    // Current vertical velocity of the bird (used for physics)
    float velocity{-gravity / 5.f};
    // Scale factor for rendering the bird's sprite
    float birdScale{1.5f};
};