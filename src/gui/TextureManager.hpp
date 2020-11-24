#pragma once
#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>
#include "Color.hpp"

namespace sgf
{
    class TextureManager
    {
    public:
        static void Init();
        static int NewTexture(const std::string& path);
        static int NewText(const std::string& text, const std::string& font, int fontSize, Color color);
        static SDL_Texture* LoadTexture(int ID);
        static void DeleteTexture(int ID);
    private:
        inline static int m_ID = 0;
        inline static std::unordered_map<int, SDL_Texture*> m_textures;
    };
}