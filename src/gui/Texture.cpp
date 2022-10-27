#include "gui/Texture.hpp"
#include "engine/Engine.hpp"
#include "engine/Error.hpp"
#include <SDL2/SDL_image.h>
#include <algorithm>

namespace sgf
{
    Texture::Texture(const std::string& path) noexcept : m_texturePtr{nullptr}, m_path{path}, m_active{true}
    {
        MakeTexture();
    }

    SDL_Texture* Texture::LoadTexture() const
    {
        return m_texturePtr;
    }

    void Texture::SetAlpha(int alpha)
    {
        SDL_SetTextureAlphaMod(m_texturePtr, alpha);
    }

    void Texture::SetPath(const std::string& path)
    {
        m_path = path;
        MakeTexture();
    }

    void Texture::SetContainerSize(int width, int height)
    {
        m_rect.w = width;    
        m_rect.h = height;
    }

    void Texture::SetContainerPosition(int x, int y)
    {
        m_rect.x = x;
        m_rect.y = y;
    }

    void Texture::Delete()
    {
        if(m_active)
        {
            SDL_DestroyTexture(m_texturePtr);
            m_texturePtr = nullptr;
            m_active = false;
        }
    }

    bool Texture::IsDeleted() const
    {
        return !m_active;
    }

    void Texture::MakeTexture()
    {
        SDL_Surface* loadedSurface = IMG_Load(m_path.c_str());

        if(!loadedSurface)
        {
            error::GetSDLError<error::Type::IMAGE>(m_path);
        }
        else
        {
            m_texturePtr = SDL_CreateTextureFromSurface(Engine::renderer, loadedSurface);
            if(!m_texturePtr)
            {
                error::GetSDLError("Texture failed to create", m_path);
            }

            SDL_FreeSurface(loadedSurface);
        }

        SDL_SetTextureBlendMode(m_texturePtr, SDL_BLENDMODE_BLEND);
    }

    void Texture::Draw(int angle)
    {
       SDL_RenderCopyEx(Engine::renderer, m_texturePtr, nullptr, &m_rect, angle, nullptr, SDL_FLIP_NONE);
    }
}
