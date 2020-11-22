#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <string>

namespace sgf
{
    class TextureManager
    {
    public:
        static void Init();
        static SDL_Texture* LoadTexture(const std::string& path);
        
    private:
        static inline int m_ID = 0;
        static inline std::vector<SDL_Texture*> m_textures;
        static inline SDL_Texture* m_texture = nullptr;
    };
}