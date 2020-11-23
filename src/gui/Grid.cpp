#include "Grid.hpp"

namespace sgf 
{
    Grid::Grid(int squareHeight, int squareWidth, int height, int width, Vertex position)
    {
        m_squareHeight = squareHeight;
        m_squareWidth = squareWidth;
        m_height = height;
        m_width = width;
        m_squareCount = height*width;
        m_position = position;

        m_polygons = new Polygon[m_squareCount];
        
        CreateBoard();
    }

    void Grid::SetHeight(int height) 
    {
        m_height = height;
    }

    void Grid::SetWidth(int width)
    {
        m_width = width;
    }

    void Grid::SetSquareHeight(int squareHeight)
    {
        m_squareHeight = squareHeight;
    }

    void Grid::SetSquareWidth(int squareWidth)
    {
        m_squareWidth = squareWidth;
    }

    int Grid::GetHeight() const
    {
        return m_height;
    }

    int Grid::GetWidth() const
    {
        return m_width;
    }

    int Grid::GetSquareCount() const
    {
        return m_squareCount;
    }

    int Grid::GetSquareHeight() const
    {
        return m_squareHeight;
    }
    
    int Grid::GetSquareWidth() const
    {
        return m_squareWidth;
    }

    void Grid::CreateBoard()
    {
        m_polygons = new Polygon[m_squareCount];

        int posX = 0;
        int posY = 0;
        for(int i = 0; i < m_squareCount; i++)
        {
            m_polygons[i].SetVertices(
                Vertex{m_position.x + posX, m_position.y + posY},
                Vertex{m_position.x + posX + m_squareWidth, m_position.y + posY},
                Vertex{m_position.x + posX + m_squareWidth, m_position.y + posY + m_squareHeight},
                Vertex{m_position.x + posX, m_position.y + posY + m_squareHeight}
            );

            posX += m_squareWidth;
            if((i+1)%m_width == 0)
            {
                posY += m_squareHeight;
                posX = 0;
            }
        }
    }

    void Grid::Draw()
    {
        for(int i = 0; i < m_squareCount; i++)
        {
            m_polygons[i].Draw();
        }
    }
}