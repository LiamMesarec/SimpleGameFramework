#pragma once

namespace sgf
{
    struct Color
    {
        int r, g, b, a = 0;

        bool operator==(const Color& other)
        {
            return(this->r == other.r
                && this->g == other.g
                && this->b == other.b
                && this->a == other.a);
        }
    };

    static constexpr int noAlpha = 255;

    static constexpr Color noColor{0,0,0,0};
    static constexpr Color red{255,0,0,noAlpha};
    static constexpr Color blue{0,0,255,noAlpha};
    static constexpr Color green{0,255,0,noAlpha};
    static constexpr Color black{0,0,0,noAlpha};
    static constexpr Color white{255,255,255,noAlpha};
}