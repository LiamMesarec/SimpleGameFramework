#include "Mouse.hpp"
#include <iostream>

namespace sgf::input
{
    math::Vertex Mouse::GetPosition()
    {
        math::Vertex pos = {0, 0};

        SDL_GetMouseState(&pos.x, &pos.y);

        return pos;
    }
}