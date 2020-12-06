#include "Polygon.hpp"
#include "../input/Mouse.hpp"
#include <memory>
#include <cmath>
#include "../math/Constants.hpp"
#include "../math/Functions.hpp"

namespace sgf
{
    Polygon::~Polygon()
    {
        Delete();
    }

    void Polygon::SetVertex(std::size_t position, Vertex vertex)
    {
        try
        {
            if(position - 1 > m_vertices.size() || position - 1 < m_vertices.size())
            {
                throw(position);
            }
        }
        catch(int exception)
        {
            error::Exception("Polygon::SetVertex", "Argument 'position' is out of bounds.", position);
        }
        
        m_vertices.at(position - 1) = vertex;
        SetRectangleForm();
    }

    void Polygon::AddVertex(Vertex vertex)
    {
        m_vertices.pop_back();
        m_vertices.push_back(vertex);
        m_vertices.push_back(m_vertices.at(0));
    }

    void Polygon::SetPosition(float x, float y)
    {
        Vertex centerPoint = GetCenterCoords();
        Vertex newCenterPoint = {x, y};

        for(auto& vertex : m_vertices)
        {
            vertex.x += newCenterPoint.x - centerPoint.x;
            vertex.y += newCenterPoint.y - centerPoint.y;
        }

        SetRectangleForm();
    }

    std::vector<Vertex>& Polygon::GetVertices()
    {
        return m_vertices;
    }

    Vertex Polygon::GetCenterCoords()
    {
        float minX = 0xFFFF, minY = 0xFFFF, maxX = 0, maxY = 0;
        Vertex* vertices = new Vertex[m_vertices.size()];

        for (std::size_t i = 0; i < m_vertices.size(); i++) 
        {
            vertices[i] = Vertex(m_vertices[i].x, m_vertices[i].y);
            if (vertices[i].x > maxX) maxX = vertices[i].x;
            if (vertices[i].x < minX) minX = vertices[i].x;
            if (vertices[i].y > maxY) maxY = vertices[i].y;
            if (vertices[i].y < minY) minY = vertices[i].y;
        }

        delete[] vertices;
        return {minX + ((maxX - minX) / 2), minY + ((maxY - minY) / 2)};
    }

    void Polygon::SetTransparency(bool transparency)
    {
        m_isTransparent = transparency;
    }

    void Polygon::SetColor(Color color)
    {
        m_color = color;
    }

    void Polygon::RemoveColor()
    {
        m_color = color::noColor;
    }

    void Polygon::SetOutline(Color color)
    {
        m_hasOutline = true;
        m_outlineColor = color;
    }

    void Polygon::RemoveOutline()
    {
        m_hasOutline = false;
    }

    void Polygon::SetTexture(std::string path)
    {
        m_texture = std::make_unique<Texture>(path);
        m_texture->SetContainerSize(m_rectangleForm.w, m_rectangleForm.h);
        m_texture->SetContainerPosition(m_rectangleForm.x, m_rectangleForm.y);
    }

    void Polygon::RemoveTexture()
    {
        m_texture->Delete();
        m_texture = nullptr;
    }

    void Polygon::SetText(std::string text, std::string font, int fontSize, Color color, TextAlignment alignment)
    {
        m_text = std::make_unique<Text>(text, font, fontSize, color, alignment);
        m_text->SetContainerSize(m_rectangleForm.w, m_rectangleForm.h);
        m_text->SetContainerPosition(m_rectangleForm.x, m_rectangleForm.y);
    }

    void Polygon::RemoveText()
    {
        m_text->Delete();
        m_text = nullptr;
    }

    void Polygon::SetTextFont(std::string font)
    {
        m_text->SetFont(font);
    }

    void Polygon::SetTextColor(Color color)
    {
        m_text->SetColor(color);
    }

    void Polygon::SetTextAlignment(TextAlignment alignment)
    {
        m_text->SetAlignment(alignment);
    }
    
    void Polygon::SetTextFontSize(int fontSize)
    {
        m_text->SetFontSize(fontSize);
    }

    int Polygon::GetID() const
    {
        return m_ID;
    }

    Color& Polygon::GetColor()
    {
        return m_color;
    }

    //Based on "The Point in Polygon Problem for Arbitrary Polygons" by Kai Hormann, Alexander Agathos
    //https://www.inf.usi.ch/hormann/papers/Hormann.2001.TPI.pdf
    int Polygon::Determinant(int i, SDL_Point v)
    {
        return (m_vertices.at(i).x - v.x)*(m_vertices.at(i+1).y - v.y)
                -(m_vertices.at(i+1).x - v.x)*(m_vertices.at(i).y - v.y);
    }

    //Based on "The Point in Polygon Problem for Arbitrary Polygons" by Kai Hormann, Alexander Agathos
    //https://www.inf.usi.ch/hormann/papers/Hormann.2001.TPI.pdf
    bool Polygon::Clicked()
    {
        if(!m_isDeleted)
        {
            SDL_Point v = {static_cast<int>(Mouse::GetPosition().x), static_cast<int>(Mouse::GetPosition().y)};

            if(m_vertices.at(0).y == v.y && m_vertices.at(0).x == v.x)
            {
                return true;
            }

            int winding = 0;

            for(std::size_t i = 0; i < m_vertices.size() - 1; i++)
            {
                if(m_vertices.at(i+1).y == v.y)
                {
                    if(m_vertices.at(i+1).x == v.x)
                    {
                        return true;
                    }
                    else
                    {
                        if(m_vertices.at(i).y == v.y && ((m_vertices.at(i+1).x > v.x) == (m_vertices.at(i).x < v.x)))
                        {
                            return true;
                        }
                    }
                    
                }
                if((m_vertices.at(i).y < v.y) != (m_vertices.at(i+1).y < v.y))
                {
                    if(m_vertices.at(i).x >= v.x)
                    {
                        if(m_vertices.at(i+1).x > v.x)
                        {
                            winding += 2*(m_vertices.at(i+1).y > m_vertices.at(i).y) - 1;
                        }
                        else if((Determinant(i, v) > 0) == (m_vertices.at(i+1).y > m_vertices.at(i).y))
                        {
                            winding += 2*(m_vertices.at(i+1).y > m_vertices.at(i).y) - 1;
                        }
                    }
                    else if(m_vertices.at(i+1).x > v.x)
                    {
                        if((Determinant(i, v) > 0) == (m_vertices.at(i+1).y > m_vertices.at(i).y))
                        {
                            winding += 2*(m_vertices.at(i+1).y > m_vertices.at(i).y) - 1;
                        }
                    }
                }
            }

            if(winding % 2 != 0)
                return true;
            else 
                return false;
        }

        return false;
    }

    void Polygon::Move(float x, float y)
    {
        if(!m_isDeleted)
        {
            for(auto& vertex : m_vertices)
            {
                vertex.x += x;
                vertex.y += y;
            }
        }
        
        SetRectangleForm();
    }

    void Polygon::Rotate(float degrees, bool antiClockwise)
    {
        if(!m_isDeleted)
        {
            float vX, vY;
            float centerX = GetCenterCoords().x;
            float centerY = GetCenterCoords().y;
            float sinValue = sin(Trig::DegreesToRadians(degrees));
            float cosValue = cos(Trig::DegreesToRadians(degrees));

            if(!antiClockwise)
            {
                for(auto& vertex : m_vertices)
                {
                    vX = vertex.x - centerX;
                    vY = vertex.y - centerY;

                    vertex.x = centerX + vX * cosValue - vY * sinValue;
                    vertex.y = centerY + vX * sinValue + vY * cosValue;
                }
            }
            else
            {
                for(auto& vertex : m_vertices)
                {
                    vX = vertex.x - centerX;
                    vY = vertex.y - centerY;

                    vertex.x = centerX + vX * cosValue + vY * sinValue;
                    vertex.y = centerY - vX * sinValue + vY * cosValue;
                }                
            }
            
        }
    }

    void Polygon::Draw()
    {
        if(!m_isDeleted)
        {
            SDL_Point* vertices = GetVerticesArray();

            if(!m_isTransparent)
            {
                if(m_color != color::noColor)
                {
                    SDL_SetRenderDrawColor(
                        sgf::Engine::renderer,
                        m_color.r,
                        m_color.g,
                        m_color.b,
                        m_color.a
                    );
                    Fill();
                }

                if(HasActiveTexture())
                {   
                    m_texture->Draw();
                }

                if(HasActiveText())
                {   
                    m_text->Draw();
                }

            }

            if(m_hasOutline)
            {
                SDL_SetRenderDrawColor(
                    sgf::Engine::renderer,
                    m_outlineColor.r,
                    m_outlineColor.g,
                    m_outlineColor.b,
                    m_outlineColor.a
                );
                SDL_RenderDrawLines(Engine::renderer, vertices, m_vertices.size());
            }

            delete[] vertices;
        }
    }

    //Based on "Software Rasterization Algorithms for Filling Triangles" by Bastian Molkenthin
    //http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html
    void Polygon::FillTopTriangle(SDL_Point v1, SDL_Point v2, SDL_Point v3)
    {
        float slope1 = float(v2.x - v1.x) / float(v2.y - v1.y);
        float slope2 = float(v3.x - v1.x) / float(v3.y - v1.y);

        float x1 = v1.x;
        float x2 = v1.x + 0.5f;

        const int numPoints = 2;
        SDL_Point points[numPoints];

        SDL_SetRenderDrawColor(
            sgf::Engine::renderer,
            m_color.r,
            m_color.g,
            m_color.b,
            m_color.a
        );

        for(int y = v1.y; y <= v2.y; y++)
        {
            points[0] = {static_cast<int>(x1), y};
            points[1] = {static_cast<int>(x2), y};
            SDL_RenderDrawLines(sgf::Engine::renderer, points, numPoints);
            x1 += slope1;
            x2 += slope2;
        }
    }

    //Based on "Software Rasterization Algorithms for Filling Triangles" by Bastian Molkenthin
    //http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html
    void Polygon::FillBottomTriangle(SDL_Point v1, SDL_Point v2, SDL_Point v3)
    {
        float slope1 = float(v3.x - v1.x) / float(v3.y - v1.y);
        float slope2 = float(v3.x - v2.x) / float(v3.y - v2.y);
        
        float x1 = v3.x;
        float x2 = v3.x + 0.5f;

        const int numPoints = 2;
        SDL_Point points[numPoints];

        SDL_SetRenderDrawColor(
            sgf::Engine::renderer,
            m_color.r,
            m_color.g,
            m_color.b,
            m_color.a
        );

        for(int y = v3.y; y > v1.y; y--)
        {
            points[0] = {static_cast<int>(x1), y};
            points[1] = {static_cast<int>(x2), y};
            SDL_RenderDrawLines(sgf::Engine::renderer, points, numPoints);
            x1 -= slope1;
            x2 -= slope2;
        }       
    }

    void Polygon::Fill()
    {
        SDL_Point** triangles = new SDL_Point*[m_vertices.size() + 1];
        SDL_Point centerCoords = {static_cast<int>(GetCenterCoords().x), static_cast<int>(GetCenterCoords().y)};

        for(std::size_t i = 0; i < m_vertices.size() - 1; i++)
        {
            triangles[i] = new SDL_Point[2];
            triangles[i][0] = {static_cast<int>(m_vertices.at(i).x), static_cast<int>(m_vertices.at(i).y)};
            triangles[i][1] = {static_cast<int>(m_vertices.at(i + 1).x), static_cast<int>(m_vertices.at(i + 1).y)};
        }

        for(std::size_t i = 0; i < m_vertices.size() - 1; i++)
        {
            FillTriangle(triangles[i][0], triangles[i][1], {centerCoords.x, centerCoords.y});
        }

        delete[] triangles;
    }

    //Based on "Software Rasterization Algorithms for Filling Triangles" by Bastian Molkenthin
    //http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html
    void Polygon::FillTriangle(SDL_Point v1, SDL_Point v2, SDL_Point v3)
    {
        SDL_Point vertices[3] = {v1,v2,v3};

        std::sort(vertices, vertices + 3, [](const SDL_Point &first, const SDL_Point &second){return first.y < second.y;});

        v1 = vertices[0];
        v2 = vertices[1];
        v3 = vertices[2];

        if (v2.y == v3.y)
        {
            FillTopTriangle(v1, v2, v3);
        }
        else if (v1.y == v2.y)
        {
            FillBottomTriangle(v1, v2, v3);
        }
        else
        {
            SDL_Point v4{
                static_cast<int>(v1.x + (static_cast<float>(v2.y - v1.y) 
                    / static_cast<float>(v3.y - v1.y)) * (v3.x - v1.x)), 
                v2.y
            };

            FillTopTriangle(v1, v2, v4);
            FillBottomTriangle(v2, v4, v3);
        } 
    }

    void Polygon::Delete()
    {   

        if(!m_isDeleted)
        {
            ObjectManager::DeleteObject(m_ID);
        }
        
        if(HasActiveTexture())
        {
            m_texture->Delete();
        } 

        if(HasActiveText())
        {
            m_text->Delete();
        }

        m_vertices.clear(); 
    }

    bool Polygon::IsDeleted() const 
    {
        return m_isDeleted;
    }

    void Polygon::SetRectangleForm()
    {
        SDL_Point* vertices = GetVerticesArray();

        int lowestVertexY = vertices[0].y, highestVertexY = vertices[0].y;
        int lowestVertexX = vertices[0].x, highestVertexX = vertices[0].x;

        for(auto&& vertex : m_vertices)
        {
            if(lowestVertexY > vertex.y) lowestVertexY = vertex.y;
            if(lowestVertexX > vertex.x) lowestVertexX = vertex.x;
            if(highestVertexY < vertex.y) highestVertexY = vertex.y;
            if(highestVertexX < vertex.x) highestVertexX = vertex.x;
        }

        m_rectangleForm.x = GetCenterCoords().x - (highestVertexX - lowestVertexX)/2;
        m_rectangleForm.y = GetCenterCoords().y - (highestVertexY - lowestVertexY)/2;
        m_rectangleForm.h = highestVertexY - lowestVertexY; 
        m_rectangleForm.w = highestVertexX - lowestVertexX;

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

        delete[] vertices;
    }

    SDL_Point* Polygon::GetVerticesArray()
    {
        SDL_Point* vertices = new SDL_Point[m_vertices.size()];

        for(std::size_t i = 0; i < m_vertices.size(); i++)
        {
            vertices[i] = { static_cast<int>(m_vertices.at(i).x), static_cast<int>(m_vertices.at(i).y)};
        }   

        return vertices;        
    }

    bool Polygon::HasActiveText()
    {
        if(!m_text)
        {
            return false;
        }
        else if(m_text->IsDeleted())
        {
            return false;
        }

        return true;
    }

    bool Polygon::HasActiveTexture()
    {
        if(!m_texture)
        {
            return false;
        } 
        else if(m_texture->IsDeleted())
        {
            return false;
        }

        return true;
    }
}