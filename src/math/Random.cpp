#include <random>
#include "Random.hpp"

namespace sgf
{
    namespace 
    {
        std::random_device device;
        std::default_random_engine engine(device());
    }

    int Random(int lowerBound, int upperBound)
    {
        std::uniform_int_distribution<int> uniform_dist(lowerBound, upperBound);
        return uniform_dist(engine);
    }
}