#include "Rectangle.hpp"
#include "../Engine/Engine.hpp"
#include "../Engine/ObjectManager.hpp"

namespace sgf::gui
{
    Rectangle::Rectangle(math::Vertex a, math::Vertex b, math::Vertex c, math::Vertex d, Color color, bool transparent)
    {
        m_rectangle.a = a;
        m_rectangle.b = b;
        m_rectangle.c = c;
        m_rectangle.d = d;
        m_rectangle.color = color;

        m_triangle1.SetVertices(a, b, d);
        m_triangle1.SetFillColor(color);
        m_triangle1.SetTransparency(transparent);
        m_triangle1.UsedForShapes(true);

        m_triangle2.SetVertices(c, a, d);
        m_triangle2.SetFillColor(color);
        m_triangle2.SetTransparency(transparent);
        m_triangle2.UsedForShapes(true);

        m_vertices.push_back({m_rectangle.a.x, m_rectangle.a.y});
        m_vertices.push_back({m_rectangle.b.x, m_rectangle.b.y});
        m_vertices.push_back({m_rectangle.c.x, m_rectangle.c.y});
        m_vertices.push_back({m_rectangle.d.x, m_rectangle.d.y});

        m_ID = ObjectManager::NewObject(m_vertices);
    }

    void Rectangle::SetFillColor(Color color)
    {
        m_triangle1.SetFillColor(color);
        m_triangle2.SetFillColor(color);
    }

    Color Rectangle::GetFillColor() const
    {
        return m_triangle1.GetFillColor();
    }

    void Rectangle::Move(int x, int y)
    {
        m_triangle1.Move(x, y);
        m_triangle2.Move(x, y);

        m_rectangle.a.x += x;
        m_rectangle.b.x += x;
        m_rectangle.c.x += x;
        m_rectangle.d.x += x;

        m_rectangle.a.y += y;
        m_rectangle.b.y += y;
        m_rectangle.c.y += y;
        m_rectangle.d.y += y;
    }

    void Rectangle::Draw()
    {   
        m_vertices.at(0) = {m_rectangle.a.x, m_rectangle.a.y};
        m_vertices.at(1) = {m_rectangle.b.x, m_rectangle.b.y};
        m_vertices.at(2) = {m_rectangle.c.x, m_rectangle.c.y};
        m_vertices.at(3) = {m_rectangle.d.x, m_rectangle.d.y};

        ObjectManager::UpdateObject(m_ID, m_vertices); 

        m_triangle1.Draw();
        m_triangle2.Draw();
    }

    void Rectangle::SetVertices(math::Vertex a, math::Vertex b, math::Vertex c, math::Vertex d)
    {   
        m_rectangle.a = a;
        m_rectangle.b = b;
        m_rectangle.c = c;
        m_rectangle.d = d; 

        m_triangle1.SetVertices(a, b, d);
        m_triangle2.SetVertices(c, a, d);
    }

    void Rectangle::SetPosition(int x, int y)
    {

    }

    void Rectangle::SetTransparency(bool transparent)
    {
        m_triangle1.SetTransparency(transparent);
        m_triangle2.SetTransparency(transparent);
    }

    bool Rectangle::Clicked()
    {
        if(m_triangle1.Clicked() || m_triangle2.Clicked())
        {
            return true;
        }

        return false;
    }

    int Rectangle::GetID() const
    {
        return m_ID;
    }
}