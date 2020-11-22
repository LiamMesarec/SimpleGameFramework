#pragma once
#include "Resolution.hpp"
#include <string>
#include <SDL2/SDL.h>

namespace sgf
{
    class Window
    {
    public:
        static void Create(int windowHeight, int windowWidth, const std::string& name);
        static void Create(Resolution res, const std::string& name);
        static void Close();

        static void SetSize(int width, int height);
        static int GetWidth();
        static int GetHeight();
    private:
        inline static int m_width = 0;
        inline static int m_height = 0;
        inline static SDL_Window* m_window = nullptr;
        inline static SDL_Surface* m_surface = nullptr;
    };
}