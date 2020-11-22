#pragma once
#include <SDL2/SDL.h>
#include "Window.hpp"

namespace sgf
{
    class Camera 
    {
    public:
        static void SetSize(int width, int height);
        static void SetPosition(int x, int y);
        static void Move(int x, int y);
    private:
        inline static SDL_Rect camera {0, 0, Window::GetWidth(), Window::GetHeight()};
    };
}