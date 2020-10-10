#include "Engine.hpp"
#include <iostream>
#include "Error.hpp"

namespace sgf
{
    void Engine::CreateWindow(int windowHeight, int windowWidth, const std::string& name)
    {
        if(SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            error::GetSDLError("Failed to initialize SDL!");
            return;
        }

        window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

        if(window == nullptr)
        {
            error::GetSDLError("Window failed to create");
            return;
        }

        surface = SDL_GetWindowSurface(window);

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(renderer == nullptr)
        {
            error::GetSDLError("Renderer failed to create");
            return;
        }
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    }

    void Engine::CreateWindow(Resolution res, const std::string& name)
    {
        if(SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            error::GetSDLError("Failed to initialize SDL!");
            return;
        }

        int windowHeight;
        int windowWidth;

        switch(res)
        {
            case Resolution::R_480P: windowHeight = 480; windowWidth = 854; break;    
            case Resolution::R_720P: windowHeight = 720; windowWidth = 1280; break;    
            case Resolution::R_1080P: windowHeight = 1080; windowWidth = 1920; break;   
            case Resolution::R_1440P: windowHeight = 2560; windowWidth = 1440; break;  
            case Resolution::R_2160P: windowHeight = 3840; windowWidth = 2160; break;      
        }
        window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

        if(window == nullptr)
        {
            error::GetSDLError("Window failed to create");
            return;
        }

        surface = SDL_GetWindowSurface(window);

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(renderer == nullptr)
        {
            error::GetSDLError("Renderer failed to create");
            return;
        }
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    }

    void Engine::CloseWindow()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
}