#include "Texture.hpp"
#include "../Engine/Engine.hpp"
#include "../Engine/Error.hpp"
#include "SDL2/SDL_image.h"

namespace sgf
{

    Texture::Texture(const std::string& path)
    {
        if(!LoadImage(path))
        {
            error::GetSDLError<sgf::error::Type::IMAGE>(path);
        }
    }

    Texture::~Texture()
    {
        //SDL_DestroyTexture(m_texture);
        //m_texture = nullptr;
    }

    bool Texture::LoadImage(const std::string& path)
    {
        m_texture = nullptr;
        m_texture = LoadTexture(path);

        if(m_texture == nullptr)
        {
            return false;
        }

        return true;
    }

    SDL_Texture* Texture::LoadTexture(const std::string& path)
    {
        SDL_Texture* newTexture = NULL;
        SDL_Surface* loadedSurface = IMG_Load(path.c_str());

        if(loadedSurface == nullptr)
        {
            error::GetSDLError<sgf::error::Type::IMAGE>(path);
        }
        else
        {
            newTexture = SDL_CreateTextureFromSurface(sgf::Engine::renderer, loadedSurface );
            if(newTexture == nullptr)
            {
                error::GetSDLError("Texture failed to create", path);
            }

            SDL_FreeSurface(loadedSurface);
        }

        return newTexture;
    }
}