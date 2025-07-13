#include "pipe.h"

Pipe::Pipe(Vector2 pos) : pipePos(pos) {}

Pipe::Pipe(Texture2D tex, Vector2 pos) : texture(tex), pipePos(pos) {}

Vector2& Pipe::getPos() { return pipePos; }

Texture2D Pipe::getTexture() { return texture; }

int Pipe::getWidth() { return texture.width; }

int Pipe::getHeight() { return texture.height; }

Rectangle Pipe::getUpperCollisionRec()
{
    return Rectangle{
        pipePos.x,
        static_cast<float>(win_offset),
        static_cast<float>(texture.width),
        static_cast<float>(pipePos.y - 150 - win_offset)};
}

Rectangle Pipe::getBottomCollisionRec()
{
    return Rectangle{
        pipePos.x,
        pipePos.y,
        static_cast<float>(texture.width),
        static_cast<float>(win_h + win_offset - pipePos.y)};
}