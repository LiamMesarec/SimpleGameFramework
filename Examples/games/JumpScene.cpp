#include "JumpScene.hpp"
#include <iostream>
#include <memory>
#include "GameOverScene.hpp"
#include "Shared.hpp"
#include "BossScene.hpp"

JumpScene::JumpScene([[maybe_unused]] sgf::SceneManagerPtr scene)
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

    for(int i = 0; i < numTiles; i++)
    {
        tiles.emplace_back(new sgf::Polygon{200.0f + i*100.0f, 550.0f - i*50.0f, 50, 50});
        tiles[i]->SetTexture("textures/tile.png");
        if(i == 2)
        {
            superJump.SetPosition(tiles[i]->GetVertices().at(0).x + 25, tiles[i]->GetVertices().at(0).y - 30);
        }
    }
    superJump.SetTexture("textures/superJump.png");
    portal.SetTexture("textures/portal.png");
    turtle.SetTexture("textures/turtle.png");
    gameInfo.backgroundTexture.SetTexture("textures/scene1background.png");
}

JumpScene::~JumpScene()
{
    for(int i = 0; i < numTiles; i++)
    {
        tiles[i]->Delete();
        delete tiles[i];
    }
    portal.Delete();
    turtle.Delete();
    superJump.Delete();
}

void JumpScene::Render()
{
    gameInfo.backgroundTexture.Draw();
    gameInfo.playerTexture.Draw();  
    gameInfo.floorTexture.Draw();
    portal.Draw();
    turtle.Draw();
    superJump.Draw();
    gameInfo.healthTexture.Draw();
    gameInfo.manaTexture.Draw();
    
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
    else if(!jumpingDown)
    {
        gameInfo.playerTexture.Move(0, gameInfo.gravity);
    }

    for(int i = 0; i < numTiles; i++)
    {
        sgf::ObjectCollision::CollisionNotAllowed(gameInfo.playerTexture, *tiles.at(i));
    }

    for(int i = 0; auto&& g : gameInfo.floorTexture)
    {
        if(sgf::ObjectCollision::Collided(gameInfo.playerTexture, g))
        {
            if(i >= 2 && i <= 4)
            {
                sgf::Engine::OpenScene<GameOverScene>(Result::LOSS, EScene::JUMP);
            }
            gameInfo.playerTexture.Move(0, -gameInfo.gravity);
            break;
        }

        i++;
    }

    if(sgf::ObjectCollision::Collided(gameInfo.playerTexture, portal))
    {
        sgf::Engine::OpenScene<GameOverScene>(Result::WIN, EScene::JUMP);
    }

    if(sgf::ObjectCollision::Collided(gameInfo.playerTexture, turtle))
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

    if(sgf::ObjectCollision::Collided(gameInfo.playerTexture, superJump))
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

void JumpScene::Jump()
{
    if(jump_y < jumpMaxHeight && !jumpingDown)
    {
        jump_y += jumpSpeed;
        gameInfo.playerTexture.Move(0, -jumpSpeed);
    }

    if(jump_y >= jumpMaxHeight)
    {
        jumpingDown = true;        
    }

    if(jumpingDown)
    {
        jump_y -= jumpSpeed;
        gameInfo.playerTexture.Move(0, jumpSpeed);
    }

    if(jump_y <= 0)
    {
        jumping = false;
        jumpingDown = false;
    }
}