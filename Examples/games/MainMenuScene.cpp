#include "MainMenuScene.hpp"
#include "TictactoeScene.hpp"
#include "JumpScene.hpp"

MainMenuScene::MainMenuScene(sgf::SceneManagerPtr scene)
{
    sgf::Camera::SetSceneSize(sgf::R_720P.width, sgf::R_720P.height);
    sgf::Camera::SetCameraSize(sgf::R_720P.width, sgf::R_720P.height);
    sgf::Window::SetBackgroundColor(sgf::Color{255, 255, 255});
    sgf::FPS::SetFPSLimit(60);

    title.SetText("Igre!", "fonts/HelveticaNeueLt.ttf", 50, 
        sgf::Color{255, 0, 0});
    
    tictactoe.SetColor({255, 0, 0});
    tictactoe.SetText("tictactoe", "fonts/HelveticaNeueLt.ttf", 50, 
        sgf::Color{0, 0, 255});
    
    run.SetColor({255, 0, 0});
    run.SetText("tictactoe", "fonts/HelveticaNeueLt.ttf", 50, 
        sgf::Color{0, 0, 255});
}

MainMenuScene::~MainMenuScene() 
{

}

void MainMenuScene::Render()
{
    title.Draw();
    tictactoe.Draw();
    run.Draw();
    jump.Draw();
}

void MainMenuScene::Update()
{

}

void MainMenuScene::HandleInput()
{
    while(sgf::EventManager::EventLoop())
    {   
        if(sgf::EventManager::Event == sgf::EventType::MousePressed)
        {
            if(tictactoe.Clicked())
            {
                sgf::Engine::OpenScene<TicTacToeScene>();
            }
            if(jump.Clicked())
            {
                sgf::Engine::OpenScene<JumpScene>();
            }
        }
    }
}