#pragma once

namespace sgf::math
{
    template<typename T>
    auto sqrt(T toSqr) -> decltype(toSqr*toSqr)
    {
        return toSqr*toSqr;
    }
}