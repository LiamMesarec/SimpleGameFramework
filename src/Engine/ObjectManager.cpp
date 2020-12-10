#include "../../include/engine/ObjectManager.hpp"

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
        m_objects.at(ID) = vertices;
    }

    void ObjectManager::DeleteObject(int ID)
    {
        m_objects.erase(ID);
    }
}