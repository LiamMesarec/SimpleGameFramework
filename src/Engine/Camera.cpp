#include "Camera.hpp"

namespace sgf
{
    void Camera::Move(int x, int y)
    {
        camera.x += x;
        camera.y += y;
    }
}