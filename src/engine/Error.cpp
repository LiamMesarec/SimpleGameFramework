#include "engine/Error.hpp"
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

namespace sgf::error
{
    void GetSDLError(const std::string& message)
    {
        std::cerr << "SDL ERROR: " << message << ": " << SDL_GetError();
        SDL_ClearError();
    }

    void GetSDLError(const char* message)
    {
        std::cerr << "SDL ERROR: " << message << ": " << SDL_GetError();
        SDL_ClearError();
    }

    void GetSDLError(const std::string& message, const std::string& path)
    {
        std::cerr << "SDL ERROR: " << message << "With path " << path << ": " << SDL_GetError();
        SDL_ClearError();
    }

    void GetSDLError(const char* message, const std::string& path)
    {
        std::cerr << "SDL ERROR: " << message << "With path " << path << ": " << SDL_GetError();
        SDL_ClearError();
    }

    template<>
    void GetSDLError<Type::IMAGE>(const char* message)
    {
        std::cerr << "SDL_image ERROR: " << message << " " << IMG_GetError();
    }

    template<>
    void GetSDLError<Type::IMAGE>(const std::string& message)
    {
        std::cerr << "SDL_image ERROR: " << message << " " << IMG_GetError();
    }

    template<>
    void GetSDLError<Type::TTF>(const char* message)
    {
        std::cerr << "SDL_ttf ERROR: " << message << " " << TTF_GetError();
    }

    template<>
    void GetSDLError<Type::TTF>(const std::string& message)
    {
        std::cerr << "SDL_ttf ERROR: " << message << " " << TTF_GetError();
    }

    template<>
    void GetSDLError<Type::MIXER>(const char* message)
    {
        std::cerr << "SDL_mixer ERROR: " << message << " " << Mix_GetError();
    }

    template<>
    void GetSDLError<Type::MIXER>(const std::string& message)
    {
        std::cerr << "SDL_mixer ERROR: " << message << " " << Mix_GetError();
    }

    void Exception(const char* function, const char* message, int value)
	{
		std::cerr << '\n' << "ERROR IN FUNCTION: " << function << " " << message << "With value: " << value << '\n';
	}
}
