#pragma once
#include "../../include/SGF/Core.hpp"
#include "../../include/SGF/Gui.hpp"

class MainMenuScene : public sgf::Scene 
{
public:
    explicit MainMenuScene(sgf::SceneManagerPtr scene);
    virtual ~MainMenuScene();

    void Render() override;
    void Update() override;
    void HandleInput() override;

    enum Difficulty{EASY, MEDIUM, HARD};
private:
    sgf::Polygon title{400, 0, 200, 50};
    sgf::Polygon tictactoe{300, 100, 200, 50};
    sgf::Polygon run{300, 200, 200, 50};
    sgf::Polygon jump{300, 200, 200, 50};

};