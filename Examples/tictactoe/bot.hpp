#pragma once

enum Square
{
    none, x, o
};

bool WinningCombination(Square squares[9], Square turn);

class Bot
{
public:
    Bot(){};
    void SetSquares(Square squares[9]);
    int MakeMove();
    int GetBestMove() const { return m_bestMove; };
private:   
    int Minimax(Square squares[9], Square turn, bool minimaxing);
    Square GetOpponent(Square turn) { return turn == Square::x ? Square::o : Square::x; };

    int m_bestMove = 0;
    Square m_squares[9];
};