#include "flappy.h"

void Flappy::Update(float dT, bool jumpPressed)
{
    if (jumpPressed && velocity >= gravity / 30.f)
    {
        velocity = -gravity / 5.0f;
        flappy = downflap;
    }
    velocity += InAir(pos, flappy) ? gravity * dT : 0;
    flappy = InAir(pos, flappy) ? upflap : midflap;

    pos.y += velocity * dT;
}

void Flappy::Draw()
{
    DrawTextureEx(flappy, pos, 0.f, birdScale, WHITE);
}

Rectangle Flappy::GetCollisionRect() const
{
    Rectangle birdRec = {pos.x, pos.y, (float)flappy.width, (float)flappy.height};
    return birdRec;
}

void Flappy::Reset()
{
    pos = {win_w / 4.f, (win_h / 3.f) + win_offset};
    velocity = -gravity / 5.f;
}
