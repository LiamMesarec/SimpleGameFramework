#pragma once
#include "../../include/SGF/Core.hpp"
#include "../../include/SGF/Gui.hpp"
#include "Chess.hpp"

class ChessScene : public sgf::Scene 
{
public:
    explicit ChessScene(sgf::SceneManagerPtr scene);
    virtual ~ChessScene();

    void Render() override;
    void Update() override;
    void HandleInput() override;

private:
    sgf::Grid board{80, 80, 8, 8, sgf::Vertex{100, 50}};
    Board chessboard;

    sgf::Color white{245, 245, 220, sgf::noAlpha};
    sgf::Color black{205, 133, 63, sgf::noAlpha};
};