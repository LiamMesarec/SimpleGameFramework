#pragma once
#include <vector>
#include "math/Vector.hpp"
#include "Color.hpp"
#include "Texture.hpp"
#include <iostream>
#include "engine/Error.hpp"
#include "engine/Engine.hpp"
#include "engine/ObjectManager.hpp"
#include "Text.hpp"

namespace sgf
{

    enum class Direction
    {
        Left, Right
    };

    enum class Shape
    { 
        UserDefined,
        Triangle, 
        Square, 
        Rectangle,
    };
    static constexpr int noID = -1;

    class Polygon
    {
    public:
        template<typename ...Args>
        Polygon(Vertex vertex, Args ...args) noexcept 
            : m_color{noColor},  m_isTransparent{false}, m_isDeleted{false}, m_angle{0}, 
            m_texture{nullptr}, m_text{nullptr}, m_shape{Shape::UserDefined}, m_outlineSize{0}, 
            m_outlineColor{noColor} 
        {
            m_vertices.push_back(vertex);
            m_vertices.insert(m_vertices.end(), { args... });
            m_vertices.push_back(vertex);

            m_ID = ObjectManager::NewObject(m_vertices);
        }

        Polygon() noexcept 
            : m_color{noColor}, m_isTransparent{false}, m_isDeleted{false}, m_angle{0}, 
            m_texture{nullptr}, m_text{nullptr}, m_shape{Shape::UserDefined}, m_outlineSize{0},
            m_outlineColor{noColor} 
        {}

        Polygon(float x, float y, float width, float height) noexcept;
        Polygon(float x, float y, float a) noexcept;

        ~Polygon();

        template<typename ...Args>
        void SetVertices(Vertex vertex, Args ...args) noexcept
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

            m_angle = 0;
            m_shape = Shape::UserDefined;
        }
        void SetVertex(std::size_t position, Vertex vertex);
        void AddVertex(Vertex vertex) noexcept;
        void SetPosition(float x, float y);
        void SetTransparency(bool transparency);
        void SetColor(Color color);
        void RemoveColor();
        void SetTexture(std::string path);
        void RemoveTexture();
        void SetTextureAlpha(int alpha);
        void SetText(std::string text, std::string font, int fontSize, Color color);
        void RemoveText();
        void SetTextFont(std::string font);
        void SetTextFontSize(int fontSize);
        void SetTextColor(Color color);
        void SetTextAlignment(int x, int y, int width, int height);
        void ToggleOutline(bool toggle);
        void SetOutlineSize(int size);
        void SetOutlineColor(Color color);

        Vertex GetCenterCoords();
        int GetID() const;
        std::vector<Vertex>& GetVertices();
        std::size_t GetNumberOfVertices() { return m_vertices.size(); }
        Color& GetColor();
        float GetHeight() const { return m_rectangleForm.h; };
        float GetWidth() const { return m_rectangleForm.w; };

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
        void DrawOutline();
        int Determinant(int i, SDL_Point v);
        void SetRectangleForm();
        SDL_Point* GetVerticesArray();

        bool HasActiveText();
        bool HasActiveTexture();

        int m_ID;
        std::vector<Vertex> m_vertices;
        Color m_color;

        bool m_isTransparent;
        bool m_isDeleted;

        SDL_Rect m_rectangleForm;
        int m_angle;

        std::unique_ptr<Texture> m_texture;
        std::unique_ptr<Text> m_text;

        sgf::Shape m_shape;

        int m_outlineSize;
        Color m_outlineColor;
        bool m_isOutlineActive;
    };
}
