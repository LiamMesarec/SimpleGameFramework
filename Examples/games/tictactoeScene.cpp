#include "TicTacToeScene.hpp"
#include <iostream>
#include <memory>
#include "GameOverScene.hpp"

TicTacToeScene::TicTacToeScene([[maybe_unused]] sgf::SceneManagerPtr scene)
{   
    sgf::Camera::SetSceneSize(sgf::R_720P.width, sgf::R_720P.height);
    sgf::Camera::SetCameraSize(sgf::R_720P.width, sgf::R_720P.height);
    sgf::Window::SetBackgroundColor(sgf::Color{255, 255, 255});
    sgf::FPS::SetFPSLimit(60);

    for(auto& square : board)
    {
        square.SetColor(sgf::Color{100, 0, 0});
        square.ToggleOutline(true);
        square.SetOutlineColor(sgf::Color{0, 0, 255});
        square.SetOutlineSize(1);
    }

    title.SetColor(sgf::Color{100, 100, 100});
    title.SetText("Tri v vrsto", "fonts/HelveticaNeueLt.ttf", 30, 
        sgf::Color{255, 0, 0});
    title.SetTextAlignment(200, 10, 0, 0);
}

TicTacToeScene::~TicTacToeScene()
{
    board.Delete();
    title.Delete();
}

void TicTacToeScene::Render()
{
    board.Draw();
    title.Draw();
}

void TicTacToeScene::Update()
{

}

void TicTacToeScene::HandleInput()
{
    while(sgf::EventManager::EventLoop())
    {
        if(sgf::EventManager::Event == sgf::EventType::MousePressed)
        {
            for(std::size_t i = 0; i < board.GetSquareCount(); i++)
            {
                if(board.Square(i)->Clicked() && squares[i] == Square::none)
                {
                    board.Square(i)->SetTexture("textures/x.png");
                    squares[i] = Square::x;

                    bot.SetSquares(squares);
                    bot.MakeMove();
                    board.Square(bot.GetBestMove())->SetTexture("textures/o.png");

                    bool draw = true;

                    if(WinningCombination(squares, Square::x))
                    {
                        sgf::Engine::OpenScene<GameOverScene>(Result::WIN, EScene::TICTACTOE);
                    } 
                    else
                    {
                        squares[bot.GetBestMove()] = Square::o;
                    }
                    if(WinningCombination(squares, Square::o))
                    {
                        sgf::Engine::OpenScene<GameOverScene>(Result::LOSS, EScene::TICTACTOE);
                    }

                    for(int i = 0; i < 9; i++)
                    {
                        if(squares[i] == Square::none)
                        {
                            draw = false;
                        }
                    }
                    if(draw)
                    {
                        sgf::Engine::OpenScene<GameOverScene>(Result::DRAW, EScene::TICTACTOE);
                    }
                }
            }
        }
    }
}