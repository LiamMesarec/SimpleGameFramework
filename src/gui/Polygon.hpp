#pragma once
#include <vector>
#include "../math/Vector.hpp"
#include "Color.hpp"
#include "Texture.hpp"
#include <iostream>
#include "../Engine/Error.hpp"
#include "../Engine/Engine.hpp"
#include "../Engine/ObjectManager.hpp"

namespace sgf
{
    class Polygon
    {
    public:
        template<typename ...Args>
        Polygon(Vertex vertex, Args ...args) noexcept : m_isDeleted{false}
        {
            m_vertices.push_back(vertex);
            m_vertices.insert(m_vertices.end(), { args... });
            m_vertices.push_back(vertex);

            m_ID = ObjectManager::NewObject(m_vertices);
        }

        Polygon(){}
        ~Polygon();
        template<typename ...Args>
        void SetVertices(Vertex vertex, Args ...args)
        {
            m_vertices.clear();
            m_vertices.push_back(vertex);
            m_vertices.insert(m_vertices.end(), { args... });
            m_vertices.push_back(vertex);
        }
        void SetVertex(std::size_t position, Vertex vertex);
        void SetPosition(int x, int y);
        void SetTransparency(bool transparency);
        void SetColor(Color color);
        void SetOutline();
        void SetTexture(Texture texture);

        Vertex GetCenterCoords();
        int GetID() const;
        std::vector<Vertex>& GetVertices();
        Color& GetColor();

        [[nodiscard]]bool Clicked();

        void Move(int x, int y);
        void Draw();
        void Delete();
        bool IsDeleted() const;
    private:
        void Fill();
        void FillTopTriangle(SDL_Point v1, SDL_Point v2, SDL_Point v3);
        void FillBottomTriangle(SDL_Point v1, SDL_Point v2, SDL_Point v3);
        void FillTriangle(SDL_Point v1, SDL_Point v2, SDL_Point v3);

        int Determinant(int i, SDL_Point v);

        int m_ID;
        std::vector<Vertex> m_vertices;
        Color m_color;
        Texture m_texture;
        bool m_transparency;
        bool m_isDeleted;
    };
}
