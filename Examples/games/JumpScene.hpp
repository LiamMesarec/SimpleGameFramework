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
    sgf::Polygon player{50, 720 - 100 - 100, 50, 100};
    sgf::Grid grass{100, 100, 1, 13, sgf::Vertex{0, 720 - 100}};


    std::vector<sgf::Polygon*> tiles;

    int jump_y = 1;
    bool jumping = false;
    bool jumpingDown = false;
    const int jumpMaxHeight = 120;
    const int jumpSpeed = 4;
    void Jump();
};