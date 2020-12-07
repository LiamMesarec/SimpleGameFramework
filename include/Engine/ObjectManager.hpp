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

        inline static std::unordered_map<int, std::vector<Vertex>> objects;
    private:
        inline static int m_ID;
    };
}