#pragma once
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <string>
#include "Color.hpp"
#include "../math/Vector.hpp"

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

    class Text
    {
    public:
        Text(const std::string& text, const std::string& font, int fontSize, Color color, TextAlignment alignment);
        Text()
            : m_text{""}, m_font{""}, m_fontSize{0}, m_color{color::noColor}, m_alignment{TextAlignment::Center},
            m_fontPtr{nullptr}, m_texturePtr{nullptr}, m_active{false} {}
        ~Text();
        void SetText(const std::string& text);
        void SetFont(const std::string& font);
        void SetFontSize(int fontSize);
        void SetColor(const Color& color);
        void SetAlignment(TextAlignment alignment);
        void SetContainerSize(int width, int height);
        void SetContainerPosition(int x, int y);

        int GetTextSize();
        std::string& GetText();
        std::string& GetFont();

        void Draw();
        void Delete();
        bool IsDeleted() const;
    private:
        void MakeText();
        void ReopenFont();

        std::string m_text;
        std::string m_font;
        int m_fontSize;
        Color m_color;
        TextAlignment m_alignment;

        TTF_Font* m_fontPtr;
        SDL_Texture* m_texturePtr;
        SDL_Rect m_rect;

        bool m_active;
    };
}