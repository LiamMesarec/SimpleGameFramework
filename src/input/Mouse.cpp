#include "../../include/input/Mouse.hpp"
#include "../../include/engine/Camera.hpp"

namespace sgf
{
    Vertex Mouse::GetPosition()
    {
        int x, y;

        float ratioX = Camera::GetSceneDimensions().w / Camera::GetCamera().w;
        float ratioY = Camera::GetSceneDimensions().h / Camera::GetCamera().h;
        
        SDL_GetMouseState(&x, &y);

        return {static_cast<float>(x), static_cast<float>(y)};
    }
}