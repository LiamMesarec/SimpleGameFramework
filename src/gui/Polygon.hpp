#pragma once
#include <vector>
#include "../math/Vector.hpp"
#include "Color.hpp"
#include "TextureManager.hpp"
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
        Polygon(Vertex vertex, Args ...args) noexcept :  m_ID{-1}, m_isDeleted{false}, m_textureID{-1}, m_texturePath{""}
        {
            m_vertices.push_back(vertex);
            m_vertices.insert(m_vertices.end(), { args... });
            m_vertices.push_back(vertex);

            m_ID = ObjectManager::NewObject(m_vertices);
        }

        Polygon() noexcept : m_ID{-1}, m_isDeleted{false}, m_textureID{-1}, m_texturePath{""} {}
        ~Polygon();
        template<typename ...Args>
        void SetVertices(Vertex vertex, Args ...args)
        {
            m_vertices.clear();
            m_vertices.push_back(vertex);
            m_vertices.insert(m_vertices.end(), { args... });
            m_vertices.push_back(vertex);

            if(m_ID < 0) 
            {
                m_ID = ObjectManager::NewObject(m_vertices);
            }
        }
        void SetVertex(std::size_t position, Vertex vertex);
        void SetPosition(int x, int y);
        void SetTransparency(bool transparency);
        void SetColor(Color color);
        void SetOutline();
        void SetTexture(std::string path);
        void DeleteTexture();

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

        bool m_transparency;
        bool m_isDeleted;

        int m_textureID;
        std::string m_texturePath;
        SDL_Rect m_textureRect;
    };
}
