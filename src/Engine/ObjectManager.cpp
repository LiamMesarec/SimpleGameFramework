#include "ObjectManager.hpp"
#include <iostream>

namespace sgf
{
    void ObjectManager::Init()
    {
        objects.clear();
        m_ID = 0;
    }

    int ObjectManager::NewObject(const std::vector<math::Vertex>& vertices)
    {
        objects.emplace(m_ID, vertices);
        m_ID++;
        return m_ID - 1;
    }

    void ObjectManager::UpdateObject(int ID, const std::vector<math::Vertex>& vertices)
    {
        objects.at(ID) = vertices;
    }
}