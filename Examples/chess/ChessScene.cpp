#include "ChessScene.hpp"
#include <iostream>
#include <memory>
#include "MainMenuScene.hpp"

ChessScene::ChessScene([[maybe_unused]] sgf::SceneManagerPtr scene)
{   
    sgf::Window::SetBackgroundColor(sgf::Color{0, 0, 0, 100});
    sgf::Camera::SetSceneSize(sgf::R_720P.width, sgf::R_720P.height);
    sgf::Camera::SetCameraSize(sgf::R_720P.width, sgf::R_720P.height);
    sgf::FPS::SetFPSLimit(60);

    bool pattern = true; 
    int j = 1;
    for(int i = 0; i < 64; i++)
    {
        if(i%2 == 0)
        {
            if(pattern) board.Square(i)->SetColor(black);
            else board.Square(i)->SetColor(white);
        }
        else
        {
            if(pattern) board.Square(i)->SetColor(white);
            else board.Square(i)->SetColor(black);
        }   
        if(j == 8)
        {
            pattern = !pattern;  
            j = 0; 
        }  
        j++;
    }

    chessboard.SetPosition("r4rk1/5ppp/p1p2n2/1p6/1P1Pp1P1/P3P2q/2QB4/R5RK w - - 0 1");

    for(int i = 0; i < 64; i++)
    {
        if(chessboard.GetSquare(i) == Piece::WPawn) board.Square(i)->SetTexture(wPawn);
        if(chessboard.GetSquare(i) == Piece::WQueen) board.Square(i)->SetTexture(wQueen);
        if(chessboard.GetSquare(i) == Piece::WKing) board.Square(i)->SetTexture(wKing);
        if(chessboard.GetSquare(i) == Piece::WBishop) board.Square(i)->SetTexture(wBishop);
        if(chessboard.GetSquare(i) == Piece::WRook) board.Square(i)->SetTexture(wRook);
        if(chessboard.GetSquare(i) == Piece::WKnight) board.Square(i)->SetTexture(wKnight);
        if(chessboard.GetSquare(i) == Piece::BPawn) board.Square(i)->SetTexture(bPawn);
        if(chessboard.GetSquare(i) == Piece::BQueen) board.Square(i)->SetTexture(bQueen);
        if(chessboard.GetSquare(i) == Piece::BKing) board.Square(i)->SetTexture(bKing);
        if(chessboard.GetSquare(i) == Piece::BBishop) board.Square(i)->SetTexture(bBishop);
        if(chessboard.GetSquare(i) == Piece::BRook) board.Square(i)->SetTexture(bRook);
        if(chessboard.GetSquare(i) == Piece::BKnight) board.Square(i)->SetTexture(bKnight);
    }
}

ChessScene::~ChessScene()
{
    
}

void ChessScene::Render()
{
    board.Draw();
}

void ChessScene::Update()
{
    
}

void ChessScene::HandleInput()
{
    while(sgf::EventManager::EventLoop())
    {
        if(sgf::EventManager::Event == sgf::EventType::MousePressed)
        {
            for(std::size_t i = 0; i < board.GetSquareCount(); i++)
            {
                if(board.Square(i)->Clicked())
                {

                }
            }
        }
    }
}