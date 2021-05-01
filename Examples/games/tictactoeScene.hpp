#pragma once
#include "../../include/SGF/Core.hpp"
#include "../../include/SGF/Gui.hpp"
#include "Bot.hpp"
#include "Shared.hpp"

class TicTacToeScene : public sgf::Scene 
{
public:
    explicit TicTacToeScene(sgf::SceneManagerPtr scene);
    virtual ~TicTacToeScene();

    void Render() override;
    void Update() override;
    void HandleInput() override;

private:
    sgf::Grid board{200, 200, 3, 3, sgf::Vertex{300, 100}};
    sgf::Polygon title{300, 50, 600, 50};

    Square squares[9] = {Square::none};
    Bot bot;
};