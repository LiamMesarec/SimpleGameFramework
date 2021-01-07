#include "Chess.hpp"

Board::Board()
{
    m_board.resize(64);
}

void Board::Clear()
{
    for(auto& square : m_board)
    {
        square = Piece::Empty;
    }
}

void Board::SetSquare(int i, Piece piece)
{
    m_board.at(i) = piece;
}

bool Board::SetPosition(const std::string& fen)
{
    int square;
    int aRank, aFile;

    unsigned int j = 1, i = 0;

    Clear();
    while (j <= 64)
    {
        aFile = 1 + ((j - 1) % 8);
        aRank = 8 - ((j - 1) / 8);
        square = (((aRank - 1) * 8) + (aFile - 1));

        char letter = fen.at(i);
        i++;
        switch (letter)
        {
            case 'p': m_board.at(square) = Piece::BPawn; break;
            case 'r': m_board.at(square) = Piece::BRook; break;
            case 'n': m_board.at(square) = Piece::BKnight; break;
            case 'b': m_board.at(square) = Piece::BBishop; break;
            case 'q': m_board.at(square) = Piece::BQueen; break;
            case 'k': m_board.at(square) = Piece::BKing; break;
            case 'P': m_board.at(square) = Piece::WPawn; break;
            case 'R': m_board.at(square) = Piece::WRook; break;
            case 'N': m_board.at(square) = Piece::WKnight; break;
            case 'B': m_board.at(square) = Piece::WBishop; break;
            case 'Q': m_board.at(square) = Piece::WQueen; break;
            case 'K': m_board.at(square) = Piece::WKing; break;
            case '/': j--; break;
            case '1': break;
            case '2': j++; break;
            case '3': j += 2; break;
            case '4': j += 3; break;
            case '5': j += 4; break;
            case '6': j += 5; break;
            case '7': j += 6; break;
            case '8': j += 7; break;
            case ' ': i+=2; break;
            default: return false;
        }
        j++;
    }

    i++;
    switch (fen.at(i))
    {
        case 'w': m_boardInfo.toMove = Color::White; i++; break;
        case 'b': m_boardInfo.toMove = Color::Black; i++; break;
    }

    i++;
    while(fen.at(i) != ' ')
    {
        switch (fen.at(i))
        {
            case 'K': m_boardInfo.castlingRights.white = true; break;
            case 'Q': m_boardInfo.castlingRights.white = true; break;
            case 'k': m_boardInfo.castlingRights.black = true; break;
            case 'q': m_boardInfo.castlingRights.black = true; break;
            default: 
                m_boardInfo.castlingRights.black = false;
                m_boardInfo.castlingRights.white = false;
                break;
        }
        i++;
    }

    i++;
    while(fen.at(i) != ' ')
    {
        if(fen.at(i) == '-')
            m_boardInfo.enPassant = '-';
        else
            m_boardInfo.enPassant += fen.at(i);

        i++;
    }

    i++;
    std::string halfMoveStr;
    while(fen.at(i) != ' ')
    {
        halfMoveStr += fen.at(i);
        i++;
    }
    m_boardInfo.halfMoveClock = std::stoi(halfMoveStr);

    i++;
    std::string fullMoveStr;
    while(i < fen.length())
    {
        fullMoveStr += fen.at(i);
        i++;
    }
    m_boardInfo.fullMoveClock = std::stoi(fullMoveStr);
    
    return true;
}

Piece Board::GetSquare(int i)
{
    return m_board.at(i);
}