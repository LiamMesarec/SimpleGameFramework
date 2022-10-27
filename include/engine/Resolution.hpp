#pragma once

namespace sgf
{
    struct Resolution
    {
        int width, height;
    };

    static constexpr Resolution R_480P = {854, 480};
    static constexpr Resolution R_720P = {1280, 720};
    static constexpr Resolution R_1080P = {1920, 1080};
    static constexpr Resolution R_1440P = {2560, 1440};
    static constexpr Resolution R_2160P = {3840, 2160};

}