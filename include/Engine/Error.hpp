#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace sgf::error
{
    enum class Type
    {
        IMAGE, TTF, MIXER
    };

    void GetSDLError(const std::string& message);
    void GetSDLError(const char* message);
    void GetSDLError(const std::string& message, const std::string& path);
    void GetSDLError(const char* message, const std::string& path);

    template<Type E>
    void GetSDLError(const char* message);
    template<Type E>
    void GetSDLError(const std::string& message);

    void Exception(const char* function, const char* message, int value);
}