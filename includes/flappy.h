#pragma once
#include "raylib.h"
#include "global.h"

class Flappy {
public:
    Flappy() {};
    Flappy(Vector2 startPos) : pos(startPos) {};
    Flappy(Texture2D mid, Texture2D up, Texture2D down, Vector2 startPos, float scale): midflap(mid), downflap(down), upflap(up), pos(startPos), birdScale(scale) {};
    void Update(float dT, bool jumpPressed);
    void Draw();
    Rectangle GetCollisionRect() const;
    Vector2 GetPos() { return pos; };
    void Reset();
    bool CheckInAir() {return InAir(pos, flappy);};
private:
    Texture2D midflap{LoadTexture("sprites/bluebird-midflap.png")};
    Texture2D downflap{LoadTexture("sprites/bluebird-downflap.png")};
    Texture2D upflap{LoadTexture("sprites/bluebird-upflap.png")};
    Texture2D flappy{ midflap };
    Vector2 pos{win_w / 4.f, (win_h / 3.f) + win_offset};
    float velocity{-gravity / 5.f};
    float birdScale{1.5f};
};