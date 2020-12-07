#pragma once
#include "Resolution.hpp"
#include <string>
#include <SDL2/SDL.h>
#include "../gui/Color.hpp"

namespace sgf
{
    class Window
    {
    public:
        static void Create(int windowHeight, int windowWidth, const std::string& name);
        static void Create(Resolution res, const std::string& name);
        static void Close();

        static void SetBackgroundColor(Color color);
        static Color GetBackgroundColor();
        static void RemoveBackgroundColor();
        static void SetSize(int width, int height);
        static int GetWidth();
        static int GetHeight();
    private:
        inline static Color m_color = color::noColor;
        inline static int m_width = 0;
        inline static int m_height = 0;
        inline static SDL_Window* m_window = nullptr;
        inline static SDL_Surface* m_surface = nullptr;
    };
}