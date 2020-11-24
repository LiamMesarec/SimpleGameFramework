#pragma once
#include "Polygon.hpp"
#include "../math/Vector.hpp"
#include <functional>

namespace sgf
{
    class Grid
    {
    public:
        Grid(int squareHeight, int squareWidth, int height, int width, Vertex position);

        Polygon* Square(int ID);

        Polygon* begin() { return &m_polygons[0]; };
        const Polygon* begin() const { return &m_polygons[0]; };
        Polygon* end() { return &m_polygons[m_squareCount]; };
        const Polygon* end() const { return &m_polygons[m_squareCount]; };

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
        int GetSquareCount() const;
    private:
        void CreateBoard();
        void ResizeBoardHeight();
        void ResizeBoardWidth();

        Polygon* m_polygons;
        std::size_t m_height;
        std::size_t m_width;
        int m_squareHeight;
        int m_squareWidth;
        std::size_t m_squareCount;
        Vertex m_position;
    };
}