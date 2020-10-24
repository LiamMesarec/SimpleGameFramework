#pragma once
#include <vector>

namespace sgf
{
    enum class LineType
    {
        STRAIGHT, ARC
    };

    struct Vertex
    {
        int x, y;
    };

    struct Vector
    {
        int x1, y1;
        int x2, y2;

        int magnitude;
    };

    struct Arc
    {
        std::vector<Vertex> vertices;
    };

    int DotProduct(Vertex first, Vertex second);
}