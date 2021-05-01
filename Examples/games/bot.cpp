#include "Bot.hpp"


void Bot::SetSquares(Square squares[9])
{
    for(int i = 0; i < 9; i++)
    {
        m_squares[i] = squares[i];
    }
}

int Bot::MakeMove()
{
    Minimax(m_squares, Square::o, false);

    return m_bestMove;
}

int Bot::Minimax(Square squares[9], Square turn, bool minimaxing)
{
    //player passed into function win -> +1
    //opposing player win -> -1
    //draw -> 0

    if (WinningCombination(squares, turn)) 
    {
        return 1;
    } 
    else if (WinningCombination(squares, Square::x) || WinningCombination(squares, Square::o)) 
    {
        return -1;
    }

    int move = -1;
    int score = -2;
    Square testBoard[9];

    for(int i = 0; i < 9; i++) {
        if(squares[i] == Square::none) 
        { 
            for(int j = 0; j < 9; j++)
            {
                testBoard[j] = squares[j];
            }
            testBoard[i] = turn;
            int newMoveScore = -Minimax(testBoard, GetOpponent(turn), true);
            
            if(newMoveScore > score) {
                score = newMoveScore;
                move = i;
                if(minimaxing == false) 
                {
                    m_bestMove = move;
                }
            }
        }
    }

    if (move == -1) {
      return 0;
    }

    return score;
}

bool WinningCombination(Square squares[9], Square turn)
{
    for (int i = 0; i < 9; i+=3) {
        if(squares[i] != Square::none && squares[i] == turn) {
            if (squares[i] == squares[i + 1] && 
            squares[i] == squares[i + 2]) 
            {
                return true;
            }
        }
    }
    
    for (int i = 0; i < 3; i++) {
        if(squares[i] != Square::none && squares[i] == turn) 
        {
            if (squares[i] == squares[i + 3] && 
            squares[i] == squares[i + 6]) 
            {
                return true;
            }
        }
    }
  
    if(squares[4] != Square::none && squares[4] == turn) {
        if (squares[0] == squares[4] && 
            squares[0] == squares[8]) 
        {
            return true;
        }
        if (squares[2] == squares[4] && 
            squares[2] == squares[6]) 
        {
            return true;
        }
    }

    return false;
}