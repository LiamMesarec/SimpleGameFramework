#pragma once
#include "../SGF/Core.hpp"
#include "../SGF/Gui.hpp"
#include "Bot.hpp"

class TicTacToe : public sgf::Scene 
{
public:
    explicit TicTacToe(sgf::SceneManagerPtr scene);
    virtual ~TicTacToe();

    void Render() override;
    void Update() override;
    void HandleInput() override;

private:
    sgf::Grid board{200, 200, 3, 3, sgf::Vertex{300, 50}};
    Square squares[9] = {Square::none};
    bool winFlag;
    Bot bot;
};