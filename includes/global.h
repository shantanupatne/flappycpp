#pragma once
#include "raylib.h"

// Window dimensions
const int win_w{640};         // Width of the game window in pixels
const int win_h{480};         // Height of the game window in pixels
const int win_offset{64};     // Offset from the bottom for ground or UI
const int gravity{3000};      // Gravity force applied to the player (pixels/sec^2)
const int MAX_PIPES{5};       // Maximum number of pipes on screen

/**
 * @brief Checks if the player (Flappy) is still in the air.
 *
 * Determines whether the player's position is above the ground level,
 * considering the window height and offset.
 *
 * @param pos The current position of the player (Flappy).
 * @param flappy The texture of the player (unused in this function).
 * @return true if the player is in the air, false if on or below the ground.
 */
inline bool InAir(Vector2 pos, Texture2D flappy)
{
    // Returns true if Flappy's y-position is above the ground threshold
    return pos.y < (win_h + win_offset - 90);
}