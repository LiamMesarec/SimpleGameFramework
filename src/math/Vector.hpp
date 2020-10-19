#pragma once

namespace sgf
{
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

    int DotProduct(Vertex first, Vertex second);
}