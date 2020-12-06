#pragma once
#include "Constants.hpp"

namespace sgf
{
    namespace Trig
    {
        constexpr float DegreesToRadians(int degree)
        {
            return degree * (Constants::Pi/180);
        }
    }
}