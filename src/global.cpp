#include "global.h"

bool InAir(Vector2 pos, Texture2D flappy)
{
    return pos.y < (win_h + win_offset - 90);
}