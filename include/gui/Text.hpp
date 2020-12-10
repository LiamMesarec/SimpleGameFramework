#pragma once
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <string>
#include "Color.hpp"
#include "../math/Vector.hpp"

namespace sgf
{
    class Text
    {
    public:
        Text(const std::string& text, const std::string& font, int fontSize, Color color);
        Text()
            : m_text{""}, m_font{""}, m_fontSize{0}, m_color{noColor},
            m_fontPtr{nullptr}, m_texturePtr{nullptr}, m_alignmentRect{0, 0, 0, 0}, m_active{false} {}
        ~Text();
        void SetText(const std::string& text);
        void SetFont(const std::string& font);
        void SetFontSize(int fontSize);
        void SetColor(const Color& color);
        void SetAlignment(int x, int y, int width, int height);
        void SetContainerSize(int width, int height);
        void SetContainerPosition(int x, int y);

        int GetTextSize();
        std::string& GetText();
        std::string& GetFont();

        void Draw(int angle);
        void Delete();
        bool IsDeleted() const;
    private:
        void MakeText();
        void ReopenFont();

        std::string m_text;
        std::string m_font;
        int m_fontSize;
        Color m_color;

        TTF_Font* m_fontPtr;
        SDL_Texture* m_texturePtr;
        SDL_Rect m_rect;
        SDL_Rect m_alignmentRect;

        bool m_active;
    };
}