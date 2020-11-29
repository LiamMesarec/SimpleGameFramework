#pragma once
#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>
#include "Color.hpp"
#include <vector>
#include <SDL2/SDL_ttf.h>

namespace sgf
{
    enum TextAlignment
    {
        Left, 
        Right, 
        Center,         
        Top,
        Bottom,
    };
    
    class TextureManager
    {
    public:
        static void Init();
        static int NewTexture(const std::string& path);
        static int NewText(const std::string& text, const std::string& font, int fontSize, Color color);
        static SDL_Texture* LoadTexture(int ID);
        static void DeleteTexture(int ID);
        static int GetTextSize(int ID);
    private:
        inline static int m_ID = 0;
        inline static std::unordered_map<int, SDL_Texture*> m_textures;
        inline static std::vector<TTF_Font*> m_fonts;
    };
}