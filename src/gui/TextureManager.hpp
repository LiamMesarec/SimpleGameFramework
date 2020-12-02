#pragma once
#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>
#include "Color.hpp"
#include <vector>
#include <SDL2/SDL_ttf.h>

namespace sgf
{
    class TextureManager
    {
    public:
        static void Init();
        [[nodiscard]]static int NewTexture(const std::string& path);
        [[nodiscard]]static SDL_Texture* LoadTexture(int ID);
        static void DeleteTexture(int ID);
    private:
        inline static int m_ID = 0;
        inline static std::unordered_map<int, SDL_Texture*> m_textures;
    };
}