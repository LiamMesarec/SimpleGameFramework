#include "MainMenuScene.hpp"
#include "TictactoeScene.hpp"
#include "JumpScene.hpp"
#include "BossScene.hpp"

MainMenuScene::MainMenuScene([[maybe_unused]]sgf::SceneManagerPtr scene)
{
    sgf::Camera::SetSceneSize(sgf::R_720P.width, sgf::R_720P.height);
    sgf::Camera::SetCameraSize(sgf::R_720P.width, sgf::R_720P.height);
    sgf::Window::SetBackgroundColor(sgf::Color{255, 255, 255});
    sgf::FPS::SetFPSLimit(60);

    for(int i = 0; i < Menu::SIZE; i++)
    {
        menu.emplace_back(new sgf::Polygon{500.0f, 180.0f + i*120.0f, 250, 60});
        menu[i]->SetTexture("textures/menuTextBackground.png");
    }
    menu[Menu::TICTACTOE]->SetText("Tictactoe", "fonts/HelveticaNeueLt.ttf", 50, sgf::Color{255, 0, 0});
    menu[Menu::TICTACTOE]->SetTextAlignment(20, 0, 0, 0);
    menu[Menu::GAME]->SetText("Game", "fonts/HelveticaNeueLt.ttf", 50, sgf::Color{255, 0, 0});
    menu[Menu::GAME]->SetTextAlignment(55, 0, 0, 0);
    menu[Menu::QUIT]->SetText("Quit", "fonts/HelveticaNeueLt.ttf", 50, sgf::Color{255, 0, 0});
    menu[Menu::QUIT]->SetTextAlignment(75, 0, 0, 0);

    backgroundPicture.SetTexture("textures/backgroundPicture.png");
}

MainMenuScene::~MainMenuScene() 
{
    for(int i = 0; i < Menu::SIZE; i++)
    {
        menu[i]->Delete();
        delete menu[i];
    }
}

void MainMenuScene::Render()
{
    backgroundPicture.Draw();
    for(int i = 0; i < Menu::SIZE; i++)
    {
        menu[i]->Draw();
    }
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
            if(menu[Menu::TICTACTOE]->Clicked())
            {
                sgf::Engine::OpenScene<TicTacToeScene>();
            }
            if(menu[Menu::GAME]->Clicked())
            {
                sgf::Engine::OpenScene<JumpScene>();
            }

            if(menu[Menu::QUIT]->Clicked())
            {
                sgf::Window::Close();
            }
        }
    }
}