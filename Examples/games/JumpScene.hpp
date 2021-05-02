#pragma once
#include "../../include/SGF/Core.hpp"
#include "../../include/SGF/Gui.hpp"
#include <vector>

class JumpScene : public sgf::Scene 
{
public:
    explicit JumpScene(sgf::SceneManagerPtr scene);
    virtual ~JumpScene();

    void Render() override;
    void Update() override;
    void HandleInput() override;

private:
    sgf::Polygon title{100, 100, 400, 100};
    sgf::Polygon player{50, 620 - 100 - 100, 50, 100};
    sgf::Grid grass{100, 100, 1, 13, sgf::Vertex{0, 720 - 100}};
    sgf::Polygon portal{1050, 720 - 100 - 100, 100, 100};
    sgf::Polygon sun{1000, 100, 300};
    sgf::Polygon turtle{700, 550, 100, 65};
    sgf::Polygon superJump{0, 0, 50};

    std::vector<sgf::Polygon*> tiles;
    const int numTiles = 3;

    int jump_y = 1;
    bool jumping = false;
    bool jumpingDown = false;
    int jumpMaxHeight = 120;
    const int jumpSpeed = 4;
    const int gravity = 4;
    int turtlePos = 0;
    const int maxTurtleDirection = 200;
    void Jump();
};