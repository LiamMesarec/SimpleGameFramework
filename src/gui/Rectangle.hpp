#pragma once
#include "SDL2/SDL.h"
#include "Color.hpp"
#include "Triangle.hpp"
#include "../math/Vector.hpp"
#include "../Engine/ObjectManager.hpp"

namespace sgf::gui
{
    class Rectangle
    {
    public:
        Rectangle(math::Vertex a, math::Vertex b, math::Vertex c, math::Vertex d, Color color, bool transparent);
        
        void SetFillColor(Color color);
        Color GetFillColor() const;
        
        void SetVertices(math::Vertex a, math::Vertex b, math::Vertex c, math::Vertex d);
        void SetPosition(int x, int y);
        void SetTransparency(bool transparent);

        void Move(int x, int y);

        void Draw();

        bool Clicked();
        
        int GetID() const;
    private:
        Triangle m_triangle1;
        Triangle m_triangle2;

        struct SRectangle
        {
            math::Vertex a, b, c, d;
            Color color;
        };

        SRectangle m_rectangle;

        std::vector<math::Vertex> m_vertices;
        int m_ID;
    };
}