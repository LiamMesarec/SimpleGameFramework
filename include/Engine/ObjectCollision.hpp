#pragma once
#include "../gui/Polygon.hpp"

namespace sgf
{
    class ObjectCollision
    {
    public:
        [[nodiscard]]static bool Collided(Polygon& polygon1, Polygon& polygon2);
        static bool CollisionNotAllowed(Polygon& polygon1, Polygon& polygon2);
        static void AllowCollision(int obj1ID, int obj2ID, bool allowCollision);
    private:
    };
}