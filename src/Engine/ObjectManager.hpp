#pragma once
#include <unordered_map>
#include "../math/Vector.hpp"
#include <vector>

namespace sgf
{
    class ObjectManager
    {
    public:
        static void Init();
        static int NewObject(const std::vector<math::Vertex>& vertices);
        static void UpdateObject(int ID, const std::vector<math::Vertex>& vertices);

        inline static std::unordered_map<int, std::vector<math::Vertex>> objects;
    private:
        inline static int m_ID;
    };
}