#pragma once
#include "../../include/SGF/Core.hpp"
#include "../../include/SGF/Gui.hpp"
#include "Shared.hpp"
#include <vector>

struct GameInfo
{
    sgf::Polygon playerTexture{50, 620 - 100, 50, 100};
    sgf::Grid floorTexture{100, 100, 1, 13, sgf::Vertex{0, 720 - 100}};
    sgf::Grid healthTexture{50, 50, 1, 5, sgf::Vertex{50, 50}};
    sgf::Grid manaTexture{50, 50, 1, 5, sgf::Vertex{50, 120}};
    sgf::Polygon backgroundTexture{0, 0, 1280, 620};

    int health = 5;
    int mana = 5;
    const int gravity = 4;
};

class JumpScene : public sgf::Scene 
{
public:
    explicit JumpScene(sgf::SceneManagerPtr scene);
    virtual ~JumpScene();

    void Render() override;
    void Update() override;
    void HandleInput() override;

private:
    GameInfo gameInfo;
    sgf::Polygon portal{1080, 720 - 100 - 110, 85, 110};
    sgf::Polygon turtle{700, 550, 100, 65};
    sgf::Polygon superJump{0, 0, 50};
    
    std::vector<sgf::Polygon*> tiles;

    const int numTiles = 3;

    int jump_y = 1;
    bool jumping = false;
    bool jumpingDown = false;
    int jumpMaxHeight = 120;
    const int jumpSpeed = 5;
    int turtlePos = 0;
    const int maxTurtleDirection = 200;
    void Jump();
};