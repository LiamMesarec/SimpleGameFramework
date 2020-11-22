#include "TestScene.hpp"
#include <iostream>
#include <memory>

Scene2::Scene2([[maybe_unused]] sgf::SceneManagerPtr scene)
{
    polygon.SetColor({100, 100, 100, 100});
}

Scene2::~Scene2()
{
    
}

void Scene2::Render()
{
    polygon.Draw();
}

void Scene2::Update()
{
    
}

void Scene2::HandleInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            sgf::Window::Close();
            break;
        }

        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                sgf::Window::Close();
                break;
            case SDLK_LEFT:
                    polygon.Move(-5, 0); 
                break;
            case SDLK_RIGHT:
                    polygon.Move(5, 0); 
                break;
            case SDLK_UP:
                    polygon.Move(0, -5); 
                break;
            case SDLK_DOWN:
                    polygon.Move(0, 5); 
                break;
            }
        }

        if(event.type == SDL_MOUSEBUTTONDOWN)
        {
            if(polygon.Clicked())
            {
                polygon.SetColor({sgf::Random(0, 255), sgf::Random(0, 255), sgf::Random(0, 255), 40});
            }
        }
    }
}