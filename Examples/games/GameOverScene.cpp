#include "GameOverScene.hpp"
#include "TictactoeScene.hpp"
#include <iostream>
#include <memory>
#include "MainMenuScene.hpp"
#include "JumpScene.hpp"

GameOverScene::GameOverScene([[maybe_unused]] sgf::SceneManagerPtr scene, Result winFlag, EScene previousScene)
{   
    sgf::Camera::SetSceneSize(sgf::R_720P.width, sgf::R_720P.height);
    sgf::Camera::SetCameraSize(sgf::R_720P.width, sgf::R_720P.height);
    sgf::Window::SetBackgroundColor(sgf::Color{146, 224, 236});
    sgf::FPS::SetFPSLimit(60);
    m_winFlag = winFlag;
    m_previousScene = previousScene;

    if(winFlag == Result::WIN)
    {
        playAnotherGame.SetText("You won! play another game?", "fonts/HelveticaNeueLt.ttf", 30, 
            sgf::Color{255, 0, 0});
    }
    if(winFlag == Result::LOSS)
    {
        playAnotherGame.SetText("You lost! play another game?", "fonts/HelveticaNeueLt.ttf", 30, 
            sgf::Color{0, 0, 200});
    }
    if(winFlag == Result::DRAW)
    {
        playAnotherGame.SetText("It was a draw! play another game?", "fonts/HelveticaNeueLt.ttf", 30, 
            sgf::Color{0, 0, 200});
    }

    yes.SetColor(sgf::Color{0, 200, 0});
    no.SetColor(sgf::Color{200, 0, 0});
    quit.SetColor(sgf::Color{88, 88, 88});
    yes.SetText("Yes", "fonts/HelveticaNeueLt.ttf", 30, sgf::Color{255, 0, 0});
    no.SetText("No", "fonts/HelveticaNeueLt.ttf", 30, sgf::Color{0, 0, 200});
    quit.SetText("Quit", "fonts/HelveticaNeueLt.ttf", 30, sgf::Color{0, 0, 200});
    yes.SetTextAlignment(20, 10, 0, 0);
    no.SetTextAlignment(20, 10, 0, 0);
    quit.SetTextAlignment(20, 10, 0, 0);
}

GameOverScene::~GameOverScene()
{
    
}

void GameOverScene::Render()
{
    playAnotherGame.Draw();
    yes.Draw();
    no.Draw();
    quit.Draw();
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
            if(yes.Clicked())
            {
                if(m_previousScene == EScene::TICTACTOE)
                {
                    sgf::Engine::OpenScene<TicTacToeScene>();
                }
                //if(m_previousScene == EScene::RUN)
                //sgf::Engine::OpenScene<>();
                if(m_previousScene == EScene::JUMP)
                {
                    sgf::Engine::OpenScene<JumpScene>();
                }
            }

            if(no.Clicked())
            {
                sgf::Engine::OpenScene<MainMenuScene>();
            }

            if(quit.Clicked())
            {
                sgf::Window::Close();
            }
        }
    }
}