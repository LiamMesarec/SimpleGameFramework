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
        Texture(const std::string& path);
        [[nodiscard]]SDL_Texture* LoadTexture() const;
        void SetPath(const std::string& path);
        void SetContainerSize(int width, int height);
        void SetContainerPosition(int x, int y);

        void Draw();
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