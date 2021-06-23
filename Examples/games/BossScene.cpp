#include "BossScene.hpp"
#include <iostream>
#include <memory>
#include "GameOverScene.hpp"
#include "Shared.hpp"

BossScene::BossScene([[maybe_unused]] sgf::SceneManagerPtr scene)
{   
    sgf::Camera::SetSceneSize(sgf::R_720P.width, sgf::R_720P.height);
    sgf::Camera::SetCameraSize(sgf::R_720P.width, sgf::R_720P.height);
    sgf::Window::SetBackgroundColor(sgf::Color{173, 216, 230, 0});
    sgf::FPS::SetFPSLimit(60);

    for(int i = 0; auto& g : gameInfo.floorTexture)
    {
        if(i >= 2 && i <= 4)
            g.SetTexture("textures/lava.png");
        else
            g.SetTexture("textures/plains.png");

        i++;
    }

    for(auto& h : gameInfo.healthTexture)
    {
        h.SetTexture("textures/heart.png");
    }

    for(auto& m : gameInfo.manaTexture)
    {
        m.SetTexture("textures/mana.png");
    }

    gameInfo.playerTexture.SetTexture("textures/player.png");
    gameInfo.backgroundTexture.SetTexture("textures/scene2background.png");
    dragon.SetTexture("textures/dragon.png");
}

BossScene::~BossScene()
{
    gameInfo.playerTexture.Delete();
    gameInfo.floorTexture.Delete();
    gameInfo.healthTexture.Delete();
    gameInfo.manaTexture.Delete();
    gameInfo.backgroundTexture.Delete();
    dragon.Delete();
}

void BossScene::Render()
{
    gameInfo.backgroundTexture.Draw();
    gameInfo.playerTexture.Draw();  
    gameInfo.floorTexture.Draw();
    gameInfo.healthTexture.Draw();
    gameInfo.manaTexture.Draw();
    dragon.Draw();
}

void BossScene::Update()
{
    for(int i = 0; auto&& g : gameInfo.floorTexture)
    {
        if(sgf::ObjectCollision::Collided(gameInfo.playerTexture, g))
        {
            if(i >= 2 && i <= 4)
            {
                sgf::Engine::OpenScene<GameOverScene>(Result::LOSS, EScene::JUMP);
            }
            gameInfo.playerTexture.Move(0, -gravity);
            break;
        }

        i++;
    }
}

void BossScene::HandleInput()
{
    while(sgf::EventManager::EventLoop())
    {
        if(sgf::EventManager::Event == sgf::EventType::KeyPressed)
        {
            if(sgf::EventManager::ActiveKey == sgf::Key::D)
            {
                gameInfo.playerTexture.Move(3, 0);
            }
            if(sgf::EventManager::ActiveKey == sgf::Key::A)
            {
                gameInfo.playerTexture.Move(-3, 0);
            }
            if(sgf::EventManager::ActiveKey == sgf::Key::W)
            {
                jumping = true;
            }
        }
    }
}