#include "Mouse.hpp"
#include <iostream>

namespace sgf
{
    Vertex Mouse::GetPosition()
    {
        Vertex pos = {0, 0};

        SDL_GetMouseState(&pos.x, &pos.y);

        return pos;
    }
}