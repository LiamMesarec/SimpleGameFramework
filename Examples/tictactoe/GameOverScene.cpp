#include "GameOverScene.hpp"
#include <iostream>
#include <memory>

GameOverScene::GameOverScene([[maybe_unused]] sgf::SceneManagerPtr scene, bool winFlag)
{   
    sgf::Window::SetBackgroundColor(sgf::Color{0, 0, 0, 0});
    m_winFlag = winFlag;

    m_rectangle.SetColor(sgf::Color{200, 200, 200, 0});
    m_rectangle.SetText("Game over, play another game?", "fonts/HelveticaNeueLt.ttf", 30, 
        sgf::Color{255, 0, 0, 150});
}

GameOverScene::~GameOverScene()
{
    
}

void GameOverScene::Render()
{
    m_rectangle.Draw();
}

void GameOverScene::Update()
{

}

void GameOverScene::HandleInput()
{
    while(sgf::EventManager::EventLoop())
    {
        if(sgf::EventManager::Event == sgf::EventType::MousePressed)
        {
            

        }
    }
}