#include "Window.hpp"
#include "SDL2/SDL.h"
#include "Engine.hpp"
#include "Error.hpp"
#include "Camera.hpp"

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
        //Camera::SetSize(windowWidth, windowHeight);

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
    }

    void Window::Create(Resolution res, const std::string& name)
    {
        if(SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            error::GetSDLError("Failed to initialize SDL!");
            return;
        }

        m_window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, res.width, res.height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        //Camera::SetSize(res.width, res.height);

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
    }

    void Window::Close()
    {
        SDL_DestroyRenderer(Engine::renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
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
}