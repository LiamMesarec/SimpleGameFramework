#include "TextureManager.hpp"
#include "../Engine/Engine.hpp"
#include "../Engine/Error.hpp"
#include "SDL2/SDL_image.h"

namespace sgf
{
    void TextureManager::Init()
    {
        for(auto rit = m_textures.rbegin(); rit != m_textures.rend(); rit++) 
        {
            SDL_DestroyTexture(*rit);
            m_textures.pop_back();
        }
    }

    SDL_Texture* TextureManager::LoadTexture(const std::string& path)
    {
        SDL_Texture* newTexture = nullptr;
        SDL_Surface* loadedSurface = IMG_Load(path.c_str());

        if(loadedSurface == nullptr)
        {
            error::GetSDLError<error::Type::IMAGE>(path);
        }
        else
        {
            newTexture = SDL_CreateTextureFromSurface(Engine::renderer, loadedSurface);
            if(newTexture == nullptr)
            {
                error::GetSDLError("Texture failed to create", path);
            }

            SDL_FreeSurface(loadedSurface);
        }

        return newTexture;
    }
}
