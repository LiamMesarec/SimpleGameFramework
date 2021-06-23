#pragma once
#include "../../include/SGF/Core.hpp"
#include "../../include/SGF/Gui.hpp"
#include "JumpScene.hpp"

class BossScene : public sgf::Scene 
{
public:
    explicit BossScene(sgf::SceneManagerPtr scene);
    virtual ~BossScene();

    void Render() override;
    void Update() override;
    void HandleInput() override;

private:
    GameInfo gameInfo;
    sgf::Polygon dragon{900, 620 - 366, 440, 366};
    const int numTiles = 3;

    int jump_y = 1;
    bool jumping = false;
    bool jumpingDown = false;
    int jumpMaxHeight = 120;
    const int jumpSpeed = 5;
    const int gravity = 4;
    void Jump();
};