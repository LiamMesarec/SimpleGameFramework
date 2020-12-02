#include "TextureManager.hpp"
#include "../Engine/Engine.hpp"
#include "../Engine/Error.hpp"
#include <SDL2/SDL_image.h>
#include <algorithm>

namespace sgf
{
    void TextureManager::Init()
    {
        for(auto& texture : m_textures) 
        {
            SDL_DestroyTexture(texture.second);
        }

        m_textures.clear();
        m_ID = 0;
    }

    int TextureManager::NewTexture(const std::string& path)
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

        m_textures.emplace(m_ID, newTexture);
        m_ID++;
        return m_ID - 1;
    }

    SDL_Texture* TextureManager::LoadTexture(int ID)
    {
        return m_textures.at(ID);
    }

    void TextureManager::DeleteTexture(int ID)
    {
        SDL_DestroyTexture(m_textures.at(ID));
        m_textures.erase(ID);
    }
}
