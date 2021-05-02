#include "JumpScene.hpp"
#include <iostream>
#include <memory>
#include "GameOverScene.hpp"
#include "Shared.hpp"

JumpScene::JumpScene([[maybe_unused]] sgf::SceneManagerPtr scene)
{   
    sgf::Camera::SetSceneSize(sgf::R_720P.width, sgf::R_720P.height);
    sgf::Camera::SetCameraSize(sgf::R_720P.width, sgf::R_720P.height);
    sgf::Window::SetBackgroundColor(sgf::Color{173, 216, 230, 0});
    sgf::FPS::SetFPSLimit(60);

    title.SetText("Zanimiva igra...", "fonts/HelveticaNeueLt.ttf", 30, 
        sgf::Color{255, 0, 0, 0});

    for(int i = 0; auto& g : grass)
    {
        if(i >= 2 && i <= 4)
            g.SetTexture("textures/lava.png");
        else
            g.SetTexture("textures/plains.png");

        i++;
    }

    player.SetTexture("textures/player.png");

    for(int i = 0; i < numTiles; i++)
    {
        tiles.emplace_back(new sgf::Polygon{200.0f + i*100.0f, 550.0f - i*50.0f, 50, 50});
        tiles[i]->SetColor({100, 0, 0});
        if(i == 2)
        {
            superJump.SetPosition(tiles[i]->GetVertices().at(0).x + 25, tiles[i]->GetVertices().at(0).y - 30);
        }
    }
    superJump.SetTexture("textures/superJump.png");
    portal.SetTexture("textures/portal.png");
    sun.SetTexture("textures/sun.png");
    turtle.SetTexture("textures/turtle.png");
}

JumpScene::~JumpScene()
{
    for(int i = 0; i < numTiles; i++)
    {
        tiles[i]->Delete();
        delete tiles[i];
    }

    player.Delete();
    title.Delete();
    grass.Delete();
    portal.Delete();
    sun.Delete();
    turtle.Delete();
    superJump.Delete();
}

void JumpScene::Render()
{
    player.Draw();  
    title.Draw();
    grass.Draw();
    portal.Draw();
    sun.Draw();
    turtle.Draw();
    superJump.Draw();

    for(int i = 0; i < numTiles; i++)
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
    else 
    {
        player.Move(0, gravity);
    }

    for(int i = 0; i < numTiles; i++)
    {
        sgf::ObjectCollision::CollisionNotAllowed(player, *tiles.at(i));
    }

    for(int i = 0; auto&& g : grass)
    {
        if(sgf::ObjectCollision::Collided(player, g))
        {
            if(i >= 2 && i <= 4)
            {
                sgf::Engine::OpenScene<GameOverScene>(Result::LOSS, EScene::JUMP);
            }
            player.Move(0, -gravity);
            break;
        }

        i++;
    }

    if(sgf::ObjectCollision::Collided(player, portal))
    {
        sgf::Engine::OpenScene<GameOverScene>(Result::WIN, EScene::JUMP);
    }

    if(sgf::ObjectCollision::Collided(player, turtle))
    {
        sgf::Engine::OpenScene<GameOverScene>(Result::LOSS, EScene::JUMP);
    }

    if(turtlePos >= -maxTurtleDirection && turtlePos < 0)
    {
        turtle.RemoveTexture();
        turtle.SetTexture("textures/turtleRight.png");
        turtle.Move(0.5, 0);
        turtlePos++;
    }

    if(turtlePos == 0)
    {
        turtlePos = maxTurtleDirection;
    }
    
    if(turtlePos <= maxTurtleDirection && turtlePos > 0)
    {
        turtle.RemoveTexture();
        turtle.SetTexture("textures/turtle.png");
        turtle.Move(-0.5, 0);
        turtlePos--;
    }

    if(turtlePos == 0)
    {
        turtlePos = -maxTurtleDirection;
    }

    if(sgf::ObjectCollision::Collided(player, superJump))
    {
        superJump.RemoveTexture();
        jumpMaxHeight = 300;
    }

}

void JumpScene::HandleInput()
{
    while(sgf::EventManager::EventLoop())
    {
        if(sgf::EventManager::Event == sgf::EventType::KeyPressed)
        {
            if(sgf::EventManager::ActiveKey == sgf::Key::D)
            {
                player.Move(3, 0);
            }
            if(sgf::EventManager::ActiveKey == sgf::Key::A)
            {
                player.Move(-3, 0);
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