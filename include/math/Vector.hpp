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
        float x, y;
        LineType type = LineType::STRAIGHT;  
    };

    struct Curve
    {
        Vertex startVertex;
        Vertex endVertex;
        Vertex middlePoint;
    };
}