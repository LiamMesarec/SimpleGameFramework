#pragma once
#include "SDL2/SDL.h"
#include "../Engine/Error.hpp"

namespace sgf
{
    class Texture
    {
    public:
        Texture(const std::string& path);
        Texture(){}
        ~Texture();
    private:
        bool LoadImage(const std::string& path);
        SDL_Texture* LoadTexture(const std::string& path);

        SDL_Texture* m_texture;
    };
}