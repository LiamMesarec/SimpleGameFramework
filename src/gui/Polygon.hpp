#pragma once
#include <vector>
#include "../math/Vector.hpp"
#include "Color.hpp"
#include "Texture.hpp"
#include <iostream>
#include "../Engine/Error.hpp"
#include "../Engine/Engine.hpp"
#include "../Engine/ObjectManager.hpp"
#include "Text.hpp"

namespace sgf
{

    enum class Direction
    {
        Left, Right
    };

    class Polygon
    {
    public:
        template<typename ...Args>
        Polygon(Vertex vertex, Args ...args) noexcept 
            :  m_ID{-1}, m_color{color::noColor}, m_outlineColor{color::noColor}, m_hasOutline{false}, 
                m_isTransparent{false}, m_isDeleted{false}, m_texture{nullptr}, m_text{nullptr}
        {
            m_vertices.push_back(vertex);
            m_vertices.insert(m_vertices.end(), { args... });
            m_vertices.push_back(vertex);

            m_ID = ObjectManager::NewObject(m_vertices);
            SetRectangleForm();
            if(HasActiveText())
            {   
                m_text->SetContainerSize(m_rectangleForm.w, m_rectangleForm.h);
                m_text->SetContainerPosition(m_rectangleForm.x, m_rectangleForm.y);
            }
            if(HasActiveTexture())
            {   
                m_texture->SetContainerSize(m_rectangleForm.w, m_rectangleForm.h);
                m_texture->SetContainerPosition(m_rectangleForm.x, m_rectangleForm.y);
            }
        }

        Polygon() noexcept 
            : m_ID{-1}, m_color{color::noColor}, m_outlineColor{color::noColor}, m_hasOutline{false}, 
                m_isTransparent{false}, m_isDeleted{false}, m_texture{nullptr},  m_text{nullptr}
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
            if(HasActiveText())
            {   
                m_text->SetContainerSize(m_rectangleForm.w, m_rectangleForm.h);
                m_text->SetContainerPosition(m_rectangleForm.x, m_rectangleForm.y);
            }
            if(HasActiveTexture())
            {   
                m_texture->SetContainerSize(m_rectangleForm.w, m_rectangleForm.h);
                m_texture->SetContainerPosition(m_rectangleForm.x, m_rectangleForm.y);
            }
        }
        void SetVertex(std::size_t position, Vertex vertex);
        void AddVertex(Vertex vertex);
        void SetPosition(float x, float y);
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
        void Move(float x, float y);
        void Rotate(float degrees, bool antiClockwise = false);
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

        bool HasActiveText();
        bool HasActiveTexture();

        int m_ID;
        std::vector<Vertex> m_vertices;
        Color m_color;
        Color m_outlineColor;

        bool m_hasOutline;
        bool m_isTransparent;
        bool m_isDeleted;

        SDL_Rect m_rectangleForm;

        std::unique_ptr<Texture> m_texture;
        std::unique_ptr<Text> m_text;

        const int noID = -1;
    };
}
