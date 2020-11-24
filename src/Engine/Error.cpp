#include "Error.hpp"
#include <iostream>
#include <SDL2/SDL_ttf.h>

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

    template<>
    void GetSDLError<Type::TTF>(const char* message)
    {
        std::cout << "SDL_ttf ERROR: Unable to Render text: " << message << " " << TTF_GetError();
    }

    template<>
    void GetSDLError<Type::TTF>(const std::string& message)
    {
        std::cout << "SDL_ttf ERROR: Unable to Render text: " << message << " " << TTF_GetError();
    }

    void Exception(const char* function, const char* message, int value)
	{
		std::cerr << '\n' << "ERROR IN FUNCTION: " << function << " " << message << "With value: " << value << '\n';
	}
}