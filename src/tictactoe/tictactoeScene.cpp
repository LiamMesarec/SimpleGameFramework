#include "TicTacToeScene.hpp"
#include <iostream>
#include <memory>

TicTacToe::TicTacToe([[maybe_unused]] sgf::SceneManagerPtr scene)
{   

}

TicTacToe::~TicTacToe()
{
    
}

void TicTacToe::Render()
{
    board.Draw();
}

void TicTacToe::Update()
{

}

void TicTacToe::HandleInput()
{
    while(sgf::EventManager::EventLoop())
    {
        if(sgf::EventManager::Event == sgf::EventType::KeyPressed)
        {
            if(sgf::EventManager::ActiveKey == sgf::Key::Space)
            {
                std::cout << "Success!!!!";
            }
        }

    }
}