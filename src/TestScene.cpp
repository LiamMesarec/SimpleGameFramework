#include "TestScene.hpp"
#include <iostream>
#include <memory>

TestScene::TestScene([[maybe_unused]] sgf::SceneManagerPtr scene)
{

}

TestScene::~TestScene()
{
}

void TestScene::Render()
{
    triangle.Draw();
    triangle2.Draw();
    rectangle.Draw();
}

void TestScene::Update()
{
    if(sgf::ObjectCollision::Collided(triangle.GetID(), rectangle.GetID()))
    {
        triangle.SetFillColor({sgf::math::Random(0, 255), sgf::math::Random(0, 255), sgf::math::Random(0, 255), sgf::math::Random(0, 255)});
    }
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
            case SDLK_LEFT:
                rectangle.Move(-3, 0); 
                break;
            case SDLK_RIGHT:
                rectangle.Move(3, 0); 
                break;
            case SDLK_UP:
                rectangle.Move(0, -3); 
                break;
            case SDLK_DOWN:
                rectangle.Move(0, 3); 
                break;
            }
        }

        if(event.type == SDL_MOUSEBUTTONDOWN)
        {
            if(triangle.Clicked())
            {
                triangle.SetFillColor({sgf::math::Random(0, 255), sgf::math::Random(0, 255), sgf::math::Random(0, 255), sgf::math::Random(0, 255)});
                triangle.SetPosition(sgf::math::Random(100, 800), sgf::math::Random(100, 300));
            }

            if(rectangle.Clicked())
            {
                rectangle.SetFillColor({sgf::math::Random(0, 255), sgf::math::Random(0, 255), sgf::math::Random(0, 255), sgf::math::Random(0, 255)});
            }
        }
    }
}