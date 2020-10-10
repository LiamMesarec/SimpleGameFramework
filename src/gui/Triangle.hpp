#pragma once
#include <SDL2/SDL.h>
#include "Color.hpp"
#include "../math/Vector.hpp"
#include <vector>

namespace sgf::gui
{
    class Triangle
    {
    public:
        Triangle(math::Vertex a, math::Vertex b, math::Vertex c, Color color, bool transparent, bool usedForShapes = false);
        Triangle(){}

        
        void SetFillColor(Color color);

        math::Vertex GetCenterCoords();
        Color GetFillColor() const;
        
        void SetVertices(math::Vertex a, math::Vertex b, math::Vertex c);
        void SetPosition(int x, int y);
        void SetTransparency(bool transparent);

        void Move(int x, int y);
        void RotateLeft(int degrees);
        void RotateRight(int degrees);

        [[nodiscard]] bool Clicked();

        void Draw();
        void UsedForShapes(bool isUsedForShapes);
        int GetID() const;
    private:
        void DrawFill();
        void DrawFillTop(SDL_Point v1, SDL_Point v2, SDL_Point v3);
        void DrawFillBottom(SDL_Point v1, SDL_Point v2, SDL_Point v3);

        bool m_usedForShapes;

        struct STriangle
        {
            SDL_Point a, b, c;
            Color color;
            bool transparent;
        };
        STriangle m_triangle;

        std::vector<math::Vertex> m_vertices;
        int m_ID;
    };
}