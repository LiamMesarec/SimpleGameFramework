#pragma once

namespace sgf
{
    struct Color
    {
        int r, g, b, a;
    };

    namespace color
    {
        static constexpr Color red{255,0,0,0};
        static constexpr Color blue{0,0,255,0};
        static constexpr Color green{0,255,0,0};
    }
}