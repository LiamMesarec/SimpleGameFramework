#include "TestScene.hpp"
#include <iostream>
#include <memory>

TestScene::TestScene([[maybe_unused]] sgf::SceneManagerPtr scene)
{
    polygon.SetColor({100, 100, 100, 100});
    polygon2.SetColor({200, 200, 100, 100});
    trikotnik.SetColor(sgf::color::red);
}

TestScene::~TestScene()
{
    
}

void TestScene::Render()
{
    polygon.Draw();
    polygon2.Draw();
    desno.Draw();
    trikotnik.Draw();
}

void TestScene::Update()
{
    desno.Move(1, 0);
}

void TestScene::HandleInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            sgf::Engine::CloseWindow();
            break;
        }

        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                sgf::Engine::CloseWindow();
                break;
            case SDLK_TAB:
                sgf::Engine::OpenScene<Scene2>();
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
                polygon.Move(sgf::Random(-5, 20), sgf::Random(-20, 5));

            if(polygon2.Clicked())
                polygon2.SetColor({sgf::Random(0, 255), sgf::Random(0, 255), sgf::Random(0, 255), 40});
            
            if(desno.Clicked())
                desno.SetColor({sgf::Random(0, 255), sgf::Random(0, 255), sgf::Random(0, 255), 40});
        }
    }
}