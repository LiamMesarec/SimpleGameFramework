#include "../../include/engine/ObjectManager.hpp"
#include <iostream>
namespace sgf
{
    void ObjectManager::Init()
    {
        m_objects.clear();
        m_ID = 0;
    }

    int ObjectManager::NewObject(const std::vector<Vertex>& vertices)
    {
        m_objects.emplace(m_ID, vertices);
        m_ID++;
        return m_ID - 1;
    }

    void ObjectManager::UpdateObject(int ID, const std::vector<Vertex>& vertices)
    {
        
        for(auto&& a : m_objects)
        {
            std::cout << ID << " " << a.first << std::endl;
        }

        m_objects.at(ID) = vertices;

        std::cout << m_objects.at(ID).at(0).x << std::endl;
    }

    void ObjectManager::UpdateObjectPosition(int ID, int x, int y)
    {
        for(auto& v : m_objects.at(ID))
        {
            v.x += x;
            v.y += y;
        }
    }

    void ObjectManager::DeleteObject(int ID)
    {
        m_objects.erase(ID);
    }

    std::vector<Vertex>& ObjectManager::GetObjectVertices(int ID)
    {
        return m_objects.at(ID);
    }
}