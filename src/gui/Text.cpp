#include "../../include/gui/Text.hpp"
#include "../../include/engine/Engine.hpp"
#include "../../include/gui/Texture.hpp"
#include "../../include/engine/Error.hpp"
#include <iostream>

namespace sgf
{
    Text::Text(const std::string& text, const std::string& font, int fontSize, Color color)
        : m_text{text}, m_font{font}, m_fontSize{fontSize}, m_color{color}, m_fontPtr{TTF_OpenFont(m_font.c_str(), m_fontSize)}, 
        m_texturePtr{nullptr}, m_rect{0, 0, 0, 0}, m_alignmentRect{0, 0, 0, 0}, m_active{true}
    {
        if(!m_fontPtr)
        {
            std::cout << "Failed to load font: " << TTF_GetError() << '\n';
        }
    }

    Text::~Text()
    {
        Delete();
    }

    void Text::SetText(const std::string& text)
    {
        m_text = text;
        MakeText();
    }

    void Text::SetFont(const std::string& font)
    {
        m_font = font;
        ReopenFont();     
        MakeText(); 
    }

    void Text::SetFontSize(int fontSize)
    {
        m_fontSize = fontSize;
        ReopenFont();  
        MakeText();     
    }

    void Text::SetColor(const Color& color)
    {
        m_color = color;
        MakeText();
    }

    void Text::SetAlignment(int x, int y, int width, int height)
    {
        m_alignmentRect.x = x;
        m_alignmentRect.y = y;
        m_alignmentRect.w = width;
        m_alignmentRect.h = height;
    }

    void Text::SetContainerSize(int width, int height)
    {
        m_rect.w = width;    
        m_rect.h = height;
    }

    void Text::SetContainerPosition(int x, int y)
    {
        m_rect.x = x;
        m_rect.y = y;
    }

    void Text::Draw(int angle)
    {
        SDL_Rect tmpRect;
        tmpRect.x = m_rect.x + m_alignmentRect.x;
        tmpRect.y = m_rect.y + m_alignmentRect.y; 
        tmpRect.w = m_rect.w + m_alignmentRect.w; 
        tmpRect.h = m_rect.h + m_alignmentRect.h;

        MakeText();
        SDL_QueryTexture(m_texturePtr, nullptr, nullptr, &tmpRect.w, &tmpRect.h);
        SDL_RenderCopyEx(Engine::renderer, m_texturePtr, nullptr, &tmpRect, angle, nullptr, SDL_FLIP_NONE);
        tmpRect.x = 0; tmpRect.y = 0; tmpRect.w = 0; tmpRect.h = 0;
    }

    void Text::MakeText()
    {
        m_texturePtr = nullptr;

        if(!m_active) 
        {
            m_active = true;
        }

        SDL_Surface* loadedSurface = TTF_RenderText_Blended_Wrapped(m_fontPtr, m_text.c_str(), 
        {
            static_cast<Uint8>(m_color.r), 
            static_cast<Uint8>(m_color.g), 
            static_cast<Uint8>(m_color.b),
            static_cast<Uint8>(m_color.a)            
        }, m_rect.w);

        if(!loadedSurface)
        {
            error::GetSDLError<error::Type::TTF>(m_text);
        }
        else
        {
            m_texturePtr = SDL_CreateTextureFromSurface(Engine::renderer, loadedSurface);
            if(!m_texturePtr)
            {
                error::GetSDLError("Text failed to create", m_text);
            }

            SDL_FreeSurface(loadedSurface);
        }
    }

    void Text::ReopenFont()
    {
        TTF_CloseFont(m_fontPtr);
        m_fontPtr = TTF_OpenFont(m_font.c_str(), m_fontSize);        
    }

    void Text::Delete()
    {
        if(m_fontPtr)
        {
            TTF_CloseFont(m_fontPtr); 
        }
        
        if(m_texturePtr)
        {
            SDL_DestroyTexture(m_texturePtr);
        }

        m_texturePtr = nullptr;
        m_fontPtr = nullptr;
        m_active = false;       
    }

    bool Text::IsDeleted() const
    {
        return !m_active;
    }
}