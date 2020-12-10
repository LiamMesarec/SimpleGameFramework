#pragma once
#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>
#include "Color.hpp"
#include <vector>
#include <SDL2/SDL_ttf.h>

namespace sgf
{
    class Texture
    {
    public:
        explicit Texture(const std::string& path) noexcept;
        [[nodiscard]]SDL_Texture* LoadTexture() const;
        void SetPath(const std::string& path);
        void SetContainerSize(int width, int height);
        void SetContainerPosition(int x, int y);

        void Draw(int angle);
        void Delete();
        bool IsDeleted() const;
    private:
        void MakeTexture();

        SDL_Texture* m_texturePtr;
        std::string m_path;
        bool m_active;
        SDL_Rect m_rect;
    };
}