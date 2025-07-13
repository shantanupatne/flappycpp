#pragma once
#include "raylib.h"
#include <deque>
#include <vector>

class Pipe
{
private:
    int win_w{640}, win_h{480}, win_offset{64};
    Texture2D texture{LoadTexture("sprites/pipe-green.png")};
    Vector2 pipePos{win_w, static_cast<float>(GetRandomValue(250, 450))};

public:
    Pipe() {};
    Pipe(Vector2 pos);
    Pipe(Texture2D tex, Vector2 pos);
    Vector2 &getPos();
    Texture2D getTexture();
    int getWidth();
    int getHeight();
    Rectangle getUpperCollisionRec();
    Rectangle getBottomCollisionRec();
};