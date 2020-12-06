#include "Mouse.hpp"
#include <iostream>

namespace sgf
{
    Vertex Mouse::GetPosition()
    {
        int x, y;

        SDL_GetMouseState(&x, &y);

        return {static_cast<float>(x), static_cast<float>(y)};
    }
}