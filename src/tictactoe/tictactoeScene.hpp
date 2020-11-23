#pragma once
#include "../SGF/Core.hpp"
#include "../SGF/Gui.hpp"

class TicTacToe : public sgf::Scene 
{
public:
    explicit TicTacToe(sgf::SceneManagerPtr scene);
    virtual ~TicTacToe();

    void Render() override;
    void Update() override;
    void HandleInput() override;

private:
    sgf::Grid board{20, 20, 10, 10, sgf::Vertex{0, 0}};
};