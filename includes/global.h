#pragma once
#include "raylib.h"

const int win_w{640}, win_h{480}, win_offset{64}, gravity{3000}, MAX_PIPES{5};

bool InAir (Vector2 pos, Texture2D flappy);