#pragma once
#include "Polygon.hpp"
#include "../math/Vector.hpp"
#include <functional>
#include <memory>

namespace sgf
{
    class Grid
    {
    public:
        Grid(int squareHeight, int squareWidth, int height, int width, Vertex position);
        ~Grid();

        Polygon* Square(int ID);

        Polygon* begin() { return &m_polygons[0]; };
        const Polygon* begin() const { return &m_polygons[0]; };
        Polygon* end() { return &m_polygons[GetSquareCount()]; };
        const Polygon* end() const { return &m_polygons[GetSquareCount()]; };

        void SetHeight(int height);
        void SetWidth(int width);
        void SetSquareHeight(int squareHeight);
        void SetSquareWidth(int squareWidth);
        void SetPosition();
        void Move();
        
        void Draw();
        void Delete();

        int GetHeight() const;
        int GetWidth() const;
        int GetSquareHeight() const;
        int GetSquareWidth() const;
        std::size_t GetSquareCount() const;
    private:
        void CreateBoard();
        void ResizeBoardHeight();
        void ResizeBoardWidth();

        Polygon* m_polygons;
        std::size_t m_height;
        std::size_t m_width;
        int m_squareHeight;
        int m_squareWidth;
        Vertex m_position;
    };
}