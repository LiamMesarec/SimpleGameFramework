#pragma once
#include "../gui/Polygon.hpp"

namespace sgf
{
    class ObjectCollision
    {
    public:
        static bool Collided(Polygon& polygon1, Polygon& polygon);
        static void AllowCollision(int obj1ID, int obj2ID, bool allowCollision);
    private:
    };
}