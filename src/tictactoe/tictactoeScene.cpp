#include "TicTacToeScene.hpp"
#include <iostream>
#include <memory>
#include "GameOverScene.hpp"

TicTacToe::TicTacToe([[maybe_unused]] sgf::SceneManagerPtr scene)
{   
    sgf::Window::SetBackgroundColor(sgf::Color{146, 224, 236, 0});

    for(auto& square : board)
    {
        square.SetOutline(sgf::Color{0, 0, 0, 0});
    }
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
        if(sgf::EventManager::Event == sgf::EventType::MousePressed)
        {
            for(std::size_t i = 0; i < board.GetSquareCount(); i++)
            {
                if(board.Square(i)->Clicked() && squares[i] == Square::none)
                {
                    board.Square(i)->SetTexture("src/textures/x.png");
                    squares[i] = Square::x;

                    bot.SetSquares(squares);
                    bot.MakeMove();
                    board.Square(bot.GetBestMove())->SetTexture("src/textures/o.png");

                    if(WinningCombination(squares, Square::x))
                    {
                        sgf::Engine::OpenScene<GameOverScene>(true);
                    } 
                    else
                    {
                        squares[bot.GetBestMove()] = Square::o;
                    }
                    if(WinningCombination(squares, Square::o))
                    {
                        sgf::Engine::OpenScene<GameOverScene>(false);
                    } 
                }
            }
        }
    }
}