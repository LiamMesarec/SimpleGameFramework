#include "Vector.hpp"

namespace sgf
{
    int DotProduct(Vertex first, Vertex second)
    {
       return first.x * second.x + first.y * second.y; 
    }
}