#pragma once
#include <vector>
#include "../math/Vector.hpp"
#include "Color.hpp"
#include "TextureManager.hpp"
#include <iostream>
#include "../Engine/Error.hpp"
#include "../Engine/Engine.hpp"
#include "../Engine/ObjectManager.hpp"
#include "Text.hpp"

namespace sgf
{
    class Polygon
    {
    public:
        template<typename ...Args>
        Polygon(Vertex vertex, Args ...args) noexcept 
            :  m_ID{-1}, m_color{color::noColor}, m_hasOutline{false}, m_isDeleted{false}, 
                m_textureID{-1}, m_texturePath{""}, m_text{nullptr}, m_hasText{false}
        {
            m_vertices.push_back(vertex);
            m_vertices.insert(m_vertices.end(), { args... });
            m_vertices.push_back(vertex);

            m_ID = ObjectManager::NewObject(m_vertices);
            SetRectangleForm();
            if(m_hasText)
            {   
                m_text->SetContainerSize(m_rectangleForm.w, m_rectangleForm.h);
                m_text->SetContainerPosition({m_rectangleForm.x, m_rectangleForm.y});
            }
        }

        Polygon() noexcept 
            : m_ID{-1}, m_color{color::noColor}, m_hasOutline{false}, m_isDeleted{false}, 
                m_textureID{-1}, m_texturePath{""}, m_text{nullptr}, m_hasText{false}
        {}

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
            SetRectangleForm();
            if(m_hasText)
            {   
                m_text->SetContainerSize(m_rectangleForm.w, m_rectangleForm.h);
                m_text->SetContainerPosition({m_rectangleForm.x, m_rectangleForm.y});
            }
        }
        void SetVertex(std::size_t position, Vertex vertex);
        void SetPosition(int x, int y);
        void SetTransparency(bool transparency);
        void SetColor(Color color);
        void RemoveColor();
        void SetOutline(Color color);
        void RemoveOutline();
        void SetTexture(std::string path);
        void RemoveTexture();
        void SetText(std::string text, std::string font, int fontSize, Color color, TextAlignment alignment);
        void RemoveText();
        void SetTextFont(std::string font);
        void SetTextFontSize(int fontSize);
        void SetTextColor(Color color);
        void SetTextAlignment(TextAlignment alignment);

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
        void SetRectangleForm();
        SDL_Point* GetVerticesArray();

        int m_ID;
        std::vector<Vertex> m_vertices;
        Color m_color;
        Color m_outlineColor;

        bool m_hasOutline;
        bool m_isTransparent;
        bool m_isDeleted;

        int m_textureID;
        std::string m_texturePath;
        SDL_Rect m_rectangleForm;

        std::unique_ptr<Text> m_text;
        bool m_hasText;

        const int noID = -1;
    };
}
