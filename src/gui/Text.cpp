#include "Texture.hpp"
#include "../Engine/Engine.hpp"
#include "Text.hpp"
#include "../Engine/Error.hpp"

namespace sgf
{
    Text::Text(std::string text, std::string font, int fontSize, Color color, TextAlignment alignment)
        : m_text{""}, m_font{""}, m_fontSize{0}, m_color{color::noColor}, m_alignment{TextAlignment::Center},
        m_fontPtr{nullptr}, m_texturePtr{nullptr}, m_active{false}
    {
        m_text = text;
        m_font = font;
        m_fontSize = fontSize;
        m_color = color;
        m_alignment = alignment;
        m_active = true;

        m_fontPtr = TTF_OpenFont(m_font.c_str(), m_fontSize);
        MakeText();
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

    void Text::SetAlignment(TextAlignment alignment)
    {
        m_alignment = alignment;
        switch(m_alignment)
        {
            case TextAlignment::Center:
                break;
            case TextAlignment::Left:

                break;
            case TextAlignment::Right:
                break;
            case TextAlignment::Top:
                break;
            case TextAlignment::Bottom:
                break;
        }  
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

    void Text::Draw()
    {
        SDL_QueryTexture(m_texturePtr, nullptr, nullptr, &m_rect.w, &m_rect.h);
        SDL_RenderCopy(Engine::renderer, m_texturePtr, nullptr, &m_rect);
    }

    void Text::MakeText()
    {
        m_texturePtr = nullptr;

        if(!m_active) m_active = true;

        SDL_Surface* loadedSurface = TTF_RenderText_Blended(m_fontPtr, m_text.c_str(), 
                {
                    static_cast<Uint8>(m_color.r), 
                    static_cast<Uint8>(m_color.g), 
                    static_cast<Uint8>(m_color.b), 
                    static_cast<Uint8>(m_color.a)
                });

        if(loadedSurface == nullptr)
        {
            error::GetSDLError<error::Type::TTF>(m_text);
        }
        else
        {
            m_texturePtr = SDL_CreateTextureFromSurface(Engine::renderer, loadedSurface);
            if(m_texturePtr == nullptr)
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
        SDL_DestroyTexture(m_texturePtr);
        TTF_CloseFont(m_fontPtr); 
        m_active = false;       
    }

    bool Text::IsDeleted() const
    {
        return !m_active;
    }
}