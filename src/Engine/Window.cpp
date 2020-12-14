#include "../../include/engine/Window.hpp"
#include "SDL2/SDL.h"
#include "../../include/engine/Engine.hpp"
#include "../../include/engine/Error.hpp"
#include "../../include/engine/Camera.hpp"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

namespace sgf 
{
    void Window::Create(int windowHeight, int windowWidth, const std::string& name)
    {
        if(SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            error::GetSDLError("Failed to initialize SDL!");
            return;
        }

        m_window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

        InitSDL();
    }

    void Window::Create(Resolution res, const std::string& name)
    {
        if(SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            error::GetSDLError("Failed to initialize SDL!");
            return;
        }

        m_window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, res.width, res.height, SDL_WINDOW_SHOWN);
      
        InitSDL();  
    }

    void Window::Close()
    {
        SDL_DestroyRenderer(Engine::renderer);
        SDL_DestroyWindow(m_window);      	
        TTF_Quit();
        Mix_Quit();
        SDL_Quit();
    }

    void Window::SetBackgroundColor(Color color)
    {
        m_color = color;
    }

    void Window::RemoveBackgroundColor()
    {
        m_color = noColor;
    }

    Color Window::GetBackgroundColor()
    {
        return m_color;
    }

    void Window::SetSize(int width, int height)
    {
        SDL_SetWindowSize(m_window, width, height);
        m_width = width;
        m_height = height;
    }

    int Window::GetWidth()
    {
        return m_width;
    }

    int Window::GetHeight()
    {
        return m_height;
    }

    void Window::InitSDL()
    {
        if(m_window == nullptr)
        {
            error::GetSDLError("Window failed to create");
            return;
        }

        m_surface = SDL_GetWindowSurface(m_window);

        Engine::renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
        if(Engine::renderer == nullptr)
        {
            error::GetSDLError("Renderer failed to create");
            return;
        }
        SDL_SetRenderDrawColor(Engine::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        
        if(TTF_Init() < 0) {
            error::GetSDLError<error::Type::TTF>("TTF failed to initialize");
            return;
        }

        if(Mix_OpenAudio(44100, AUDIO_S16LSB, 2, 2048 ) < 0)
        {
            error::GetSDLError<error::Type::MIXER>("Mixer failed to initialize");
            return;
        }
    }
}