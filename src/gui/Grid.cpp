#include "../../include/gui/Grid.hpp"

namespace sgf 
{
    Grid::Grid(int squareHeight, int squareWidth, std::size_t height, std::size_t width, Vertex position)
        : m_height{height},  m_width{width}, m_squareHeight{squareHeight}, m_squareWidth{squareWidth}, m_position{position}
    {
        CreateBoard();
    }

    Grid::~Grid()
    {
        Delete();
        delete[] m_polygons;
    }

    Polygon* Grid::Square(int ID)
    {
        return &m_polygons[ID];
    }

    void Grid::SetHeight(int height) 
    {
        m_height = height;
        CreateBoard();
    }

    void Grid::SetWidth(int width)
    {
        m_width = width;
        CreateBoard();
    }

    void Grid::SetSquareHeight(int squareHeight)
    {
        m_squareHeight = squareHeight;
        CreateBoard();
    }

    void Grid::SetSquareWidth(int squareWidth)
    {
        m_squareWidth = squareWidth;
        CreateBoard();
    }

    int Grid::GetHeight() const
    {
        return m_height;
    }

    int Grid::GetWidth() const
    {
        return m_width;
    }

    std::size_t Grid::GetSquareCount() const
    {
        return m_width*m_height;
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
        m_polygons = new Polygon[GetSquareCount()];

        int posX = 0;
        int posY = 0;
        for(std::size_t i = 0; i < GetSquareCount(); i++)
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
        for(std::size_t i = 0; i < GetSquareCount(); i++)
        {
            m_polygons[i].Draw();
        }
    }

    void Grid::Delete()
    {
        for(std::size_t i = 0; i < GetSquareCount(); i++)
        {
            m_polygons[i].Delete();
        }
    }
}