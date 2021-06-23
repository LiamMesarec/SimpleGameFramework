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

    enum Menu{TICTACTOE, GAME, QUIT, SIZE};
private:
    std::vector<sgf::Polygon*> menu;
    sgf::Polygon backgroundPicture{0, 0, 1280, 720};
};