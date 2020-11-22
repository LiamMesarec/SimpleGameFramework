#pragma once
#include <vector>

namespace sgf
{
    enum class LineType
    {
        STRAIGHT, CURVE
    };

    struct Vertex
    {
        int x, y;
        LineType type = LineType::STRAIGHT;  
    };

    struct Curve
    {
        Vertex startVertex;
        Vertex endVertex;
        Vertex middlePoint;
    };
}