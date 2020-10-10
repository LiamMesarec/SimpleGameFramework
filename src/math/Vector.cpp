#include "Vector.hpp"

namespace sgf::math
{
    int DotProduct(Vertex first, Vertex second)
    {
       return first.x * second.x + first.y * second.y; 
    }
}