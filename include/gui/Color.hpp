#pragma once

namespace sgf
{
    struct Color
    {
        int r, g, b, a;

        bool operator==(const Color& other)
        {
            return(this->r == other.r
                && this->g == other.g
                && this->b == other.b
                && this->a == other.a);
        }
    };

    static constexpr Color noColor{0,0,0,0};
    static constexpr Color red{255,0,0,254};
    static constexpr Color blue{0,0,255,254};
    static constexpr Color green{0,255,0,254};
}