#include "Error.hpp"
#include <iostream>

namespace sgf::error
{
    void GetSDLError(const std::string& message)
    {
        std::cout << "SDL ERROR: " << message << ": " << SDL_GetError();
        SDL_ClearError();
    }

    void GetSDLError(const char* message)
    {
        std::cout << "SDL ERROR: " << message << ": " << SDL_GetError();
        SDL_ClearError();
    }

    void GetSDLError(const std::string& message, const std::string& path)
    {
        std::cout << "SDL ERROR: " << message << "With path " << path << ": " << SDL_GetError();
        SDL_ClearError();
    }

    void GetSDLError(const char* message, const std::string& path)
    {
        std::cout << "SDL ERROR: " << message << "With path " << path << ": " << SDL_GetError();
        SDL_ClearError();
    }

    template<>
    void GetSDLError<Type::IMAGE>(const char* message)
    {
        std::cout << "SDL_image ERROR: Could not load image: " << message << " " << IMG_GetError();
    }

    template<>
    void GetSDLError<Type::IMAGE>(const std::string& message)
    {
        std::cout << "SDL_image ERROR: Could not load image: " << message << " " << IMG_GetError();
    }
}