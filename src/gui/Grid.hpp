#pragma once
#include "Polygon.hpp"
#include "../math/Vector.hpp"

namespace sgf
{
    class Grid
    {
    public:
        Grid(int squareHeight, int squareWidth, int height, int width, Vertex position);
        Polygon& Square(int ID);

        void SetHeight(int height);
        void SetWidth(int width);
        void SetSquareHeight(int squareHeight);
        void SetSquareWidth(int squareWidth);
        void SetPosition();
        void Move();
        void Draw();
        
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
        int m_height;
        int m_width;
        int m_squareHeight;
        int m_squareWidth;
        int m_squareCount;
        Vertex m_position;
    };
}