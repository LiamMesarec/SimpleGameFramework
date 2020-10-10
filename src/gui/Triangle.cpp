#include "Triangle.hpp"
#include "../Engine/Engine.hpp"
#include <algorithm>
#include "../input/Mouse.hpp"
#include "../Engine/ObjectManager.hpp"

namespace sgf::gui
{
    Triangle::Triangle(math::Vertex a, math::Vertex b, math::Vertex c, Color color, bool transparent, bool usedForShapes)
    {
        m_triangle.a = {a.x, a.y};
        m_triangle.b = {b.x, b.y};
        m_triangle.c = {c.x, c.y};

        m_triangle.color = color;
        m_triangle.transparent = transparent;

        m_usedForShapes = usedForShapes;

        if(!m_usedForShapes)
        {
            m_vertices.push_back({m_triangle.a.x, m_triangle.a.y});
            m_vertices.push_back({m_triangle.b.x, m_triangle.b.y});
            m_vertices.push_back({m_triangle.c.x, m_triangle.c.y});

            m_ID = ObjectManager::NewObject(m_vertices);
        }
    }

    void Triangle::SetFillColor(Color color)
    {
        m_triangle.color = color;
    }

    void Triangle::SetVertices(math::Vertex a, math::Vertex b, math::Vertex c)
    {
        m_triangle.a = {a.x, a.y};
        m_triangle.b = {b.x, b.y};
        m_triangle.c = {c.x, c.y};
    }

    void Triangle::SetTransparency(bool transparent)
    {
        m_triangle.transparent = transparent;
    }

    math::Vertex Triangle::GetCenterCoords()
    {
        math::Vertex centerPoint;

        centerPoint.x = (m_triangle.a.x + m_triangle.b.x + m_triangle.c.x)/3;
        centerPoint.y = (m_triangle.a.y + m_triangle.b.y + m_triangle.c.y)/3;

        return centerPoint;
    }

    Color Triangle::GetFillColor() const
    {
        return m_triangle.color;
    }

    void Triangle::SetPosition(int x, int y)
    {
        math::Vertex centerPoint = GetCenterCoords();
        math::Vertex newCenterPoint = {x, y};

        m_triangle.a.x += newCenterPoint.x - centerPoint.x;
        m_triangle.b.x += newCenterPoint.x - centerPoint.x;
        m_triangle.c.x += newCenterPoint.x - centerPoint.x;
        m_triangle.a.y += newCenterPoint.y - centerPoint.y;
        m_triangle.b.y += newCenterPoint.y - centerPoint.y;
        m_triangle.c.y += newCenterPoint.y - centerPoint.y;
    }

    bool Triangle::Clicked()
    {   
        int dot1 = (m_triangle.b.y - m_triangle.a.y) * (input::Mouse::GetPosition().x - m_triangle.a.x) + (-m_triangle.b.x + m_triangle.a.x)*(input::Mouse::GetPosition().y - m_triangle.a.y);
        int dot2 = (m_triangle.c.y - m_triangle.b.y) * (input::Mouse::GetPosition().x - m_triangle.b.x) + (-m_triangle.c.x + m_triangle.b.x)*(input::Mouse::GetPosition().y - m_triangle.b.y);
        int dot3 = (m_triangle.a.y - m_triangle.c.y) * (input::Mouse::GetPosition().x - m_triangle.c.x) + (-m_triangle.a.x + m_triangle.c.x)*(input::Mouse::GetPosition().y - m_triangle.c.y);
        
        if(dot1 >= 0 && dot2 >= 0 && dot3 >= 0)
        {
            return true;
        }

        return false;
    }

    void Triangle::DrawFill()
    {
        SDL_Point v1 = m_triangle.a;
        SDL_Point v2 = m_triangle.b;
        SDL_Point v3 = m_triangle.c;

        SDL_Point vArr[] {v1, v2, v3};
        std::sort(vArr, vArr + 3, [](const SDL_Point &first, const SDL_Point &second){return first.y < second.y;});

        v1 = vArr[0];
        v2 = vArr[1];
        v3 = vArr[2];

        if (v2.y == v3.y)
        {
            DrawFillTop(v1, v2, v3);
        }
        else if (v1.y == v2.y)
        {
            DrawFillBottom(v1, v2, v3);
        }
        else
        {
            SDL_Point v4{
                static_cast<int>(v1.x + (static_cast<float>(v2.y - v1.y) 
                    / static_cast<float>(v3.y - v1.y)) * (v3.x - v1.x)), 
                v2.y
            };

            DrawFillTop(v1, v2, v4);
            DrawFillBottom(v2, v4, v3);
        } 
    }

    void Triangle::DrawFillTop(SDL_Point v1, SDL_Point v2, SDL_Point v3)
    {
        float slope1 = float(v2.x - v1.x) / float(v2.y - v1.y);
        float slope2 = float(v3.x - v1.x) / float(v3.y - v1.y);

        float x1 = v1.x;
        float x2 = v1.x + 0.5f;

        const int numPoints = 2;
        SDL_Point points[numPoints];

        SDL_SetRenderDrawColor(
            Engine::renderer,
            m_triangle.color.r,
            m_triangle.color.g,
            m_triangle.color.b,
            m_triangle.color.a
        );

        for(int y = v1.y; y <= v2.y; y++)
        {
            points[0] = {static_cast<int>(x1), y};
            points[1] = {static_cast<int>(x2), y};
            SDL_RenderDrawLines(sgf::Engine::renderer, points, numPoints);
            x1 += slope1;
            x2 += slope2;
        }
    }

    void Triangle::DrawFillBottom(SDL_Point v1, SDL_Point v2, SDL_Point v3)
    {
        float slope1 = float(v3.x - v1.x) / float(v3.y - v1.y);
        float slope2 = float(v3.x - v2.x) / float(v3.y - v2.y);
        
        float x1 = v3.x;
        float x2 = v3.x + 0.5f;

        const int numPoints = 2;
        SDL_Point points[numPoints];

        SDL_SetRenderDrawColor(
            sgf::Engine::renderer,
            m_triangle.color.r,
            m_triangle.color.g,
            m_triangle.color.b,
            m_triangle.color.a
        );

        for(int y = v3.y; y > v1.y; y--)
        {
            points[0] = {static_cast<int>(x1), y};
            points[1] = {static_cast<int>(x2), y};
            SDL_RenderDrawLines(sgf::Engine::renderer, points, numPoints);
            x1 -= slope1;
            x2 -= slope2;
        }       
    }

    void Triangle::Draw()
    {
        SDL_Point points[4] { m_triangle.a, m_triangle.b, m_triangle.c, m_triangle.a};

        if(!m_usedForShapes)
        {
            m_vertices.at(0) = {m_triangle.a.x, m_triangle.a.y};
            m_vertices.at(1) = {m_triangle.b.x, m_triangle.b.y};
            m_vertices.at(2) = {m_triangle.c.x, m_triangle.c.y};

            ObjectManager::UpdateObject(m_ID, m_vertices);
        }

        SDL_SetRenderDrawColor(
            sgf::Engine::renderer,
            m_triangle.color.r,
            m_triangle.color.g,
            m_triangle.color.b,
            m_triangle.color.a
        );
        SDL_RenderDrawLines(sgf::Engine::renderer, points, 4);

        if(!m_triangle.transparent)
        {
            DrawFill();
        }
    }

    void Triangle::Move(int x, int y)
    {
        m_triangle.a.x += x;
        m_triangle.b.x += x;
        m_triangle.c.x += x;

        m_triangle.a.y += y;
        m_triangle.b.y += y;
        m_triangle.c.y += y;
    }

    void Triangle::RotateRight(int degrees)
    {
        //TO DO matrix transformation
        m_triangle.a.x += degrees;
        m_triangle.b.x -= degrees;
        m_triangle.c.x += degrees;

        m_triangle.a.y -= degrees;
        m_triangle.b.y += degrees;
        m_triangle.c.y += degrees;
    }

    void Triangle::UsedForShapes(bool isUsedForShapes)
    {
        m_usedForShapes = isUsedForShapes;
    }

    int Triangle::GetID() const
    {
        return m_ID;
    }
}