#include "JumpScene.hpp"
#include <iostream>
#include <memory>

JumpScene::JumpScene([[maybe_unused]] sgf::SceneManagerPtr scene)
{   
    sgf::Camera::SetSceneSize(sgf::R_720P.width, sgf::R_720P.height);
    sgf::Camera::SetCameraSize(sgf::R_720P.width, sgf::R_720P.height);
    sgf::Window::SetBackgroundColor(sgf::Color{173, 216, 230, 0});
    sgf::FPS::SetFPSLimit(60);

    title.SetText("Zanimiva igra...", "fonts/HelveticaNeueLt.ttf", 30, 
        sgf::Color{255, 0, 0, 0});

    for(auto& g : grass)
    {
        g.SetTexture("textures/plains.png");
    }

    player.SetColor(sgf::red);
    //player.SetColor({100, 100, 100});

    for(int i = 0; i < 5; i++)
    {
        tiles.emplace_back(new sgf::Polygon{200.0f + i*100.0f, 500.0f - i*50.0f, 50, 50});
        tiles[i]->SetColor({100, 0, 0});
    }
}

JumpScene::~JumpScene()
{
    for(int i = 0; i < 5; i++)
    {
        delete tiles[i];
    }
}

void JumpScene::Render()
{
    player.Draw();  
    title.Draw();
    grass.Draw();

    for(int i = 0; i < 5; i++)
    {
        tiles[i]->Draw();
    }
}

void JumpScene::Update()
{
    if(jumping)
    {
        Jump();
    }
}

void JumpScene::HandleInput()
{
    while(sgf::EventManager::EventLoop())
    {
        if(sgf::EventManager::Event == sgf::EventType::MousePressed)
        {

        }

        if(sgf::EventManager::Event == sgf::EventType::KeyPressed)
        {
            if(sgf::EventManager::ActiveKey == sgf::Key::D)
            {
                player.Move(1, 0);
            }
            if(sgf::EventManager::ActiveKey == sgf::Key::A)
            {
                player.Move(-1, 0);
            }
            if(sgf::EventManager::ActiveKey == sgf::Key::W)
            {
                jumping = true;
            }
        }
    }
}

void JumpScene::Jump()
{
    if(jump_y < jumpMaxHeight && !jumpingDown)
    {
        jump_y += jumpSpeed;
        player.Move(0, -jumpSpeed);
    }

    if(jump_y >= jumpMaxHeight)
    {
        jumpingDown = true;        
    }

    if(jumpingDown)
    {
        jump_y -= jumpSpeed;
        player.Move(0, jumpSpeed);
    }

    if(jump_y <= 0)
    {
        jumping = false;
        jumpingDown = false;
    }
}