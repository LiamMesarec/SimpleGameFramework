#pragma once 
#include <vector>
#include <string>

enum class Piece
{
    Empty = 0,
    BPawn = 1,
    BKnight = 2,
    BBishop = 3,
    BRook = 4,
    BQueen = 5,
    BKing = 6,
    WPawn = 7,
    WKnight = 8,
    WBishop = 9,
    WRook = 10,
    WQueen = 11,
    WKing = 12
};

enum class Color 
{
    White = 0, 
    Black = 1,
};

struct CastlingRights
{
    CastlingRights() : white{true}, black{true} {}
    bool white, black;
};

static constexpr auto bKing = "textures/black_king.png";
static constexpr auto bQueen = "textures/black_queen.png";
static constexpr auto bRook = "textures/black_rook.png";
static constexpr auto bBishop = "textures/black_bishop.png";
static constexpr auto bKnight = "textures/black_knight.png";
static constexpr auto bPawn = "textures/black_pawn.png";

static constexpr auto wKing = "textures/white_king.png";
static constexpr auto wQueen = "textures/white_queen.png";
static constexpr auto wRook = "textures/white_rook.png";
static constexpr auto wBishop = "textures/white_bishop.png";
static constexpr auto wKnight = "textures/white_knight.png";
static constexpr auto wPawn = "textures/white_pawn.png";

struct BoardInfo
{
    BoardInfo()
        : halfMoveClock{0}, fullMoveClock{0} {}
    CastlingRights castlingRights;
    Color toMove;
    std::string enPassant;
    int halfMoveClock;
    int fullMoveClock;
};

class Board
{
public:
    Board();
    void Clear();
    bool SetPosition(const std::string& fen);
    void SetSquare(int i, Piece piece);
    Piece GetSquare(int i);
private:
    std::vector<Piece> m_board;
    BoardInfo m_boardInfo;
};
