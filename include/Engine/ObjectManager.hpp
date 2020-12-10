#pragma once
#include <unordered_map>
#include "../math/Vector.hpp"
#include <vector>
#include <memory>

namespace sgf
{
    class ObjectManager
    {
    public:
        static void Init();
        static int NewObject(const std::vector<Vertex>& vertices);
        static void UpdateObject(int ID, const std::vector<Vertex>& polygon);
        static void DeleteObject(int ID);

    private:
        inline static std::unordered_map<int, std::vector<Vertex>> m_objects;
        inline static int m_ID;
    };
}