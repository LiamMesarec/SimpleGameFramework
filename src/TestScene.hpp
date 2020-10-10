#pragma once
#include "SGF/Core.hpp"
#include "SGF/Gui.hpp"
#include "SGF/Math.hpp"

class TestScene : public sgf::Scene 
{
public:
    explicit TestScene(sgf::SceneManagerPtr scene);
    virtual ~TestScene();

    void Render() override;
    void Update() override;
    void HandleInput() override;

private:
    sgf::gui::Triangle triangle{
        {100, 400}, {500, 200}, {300, 100}, 
        {0, 0, 0, 0}, false
    };

    sgf::gui::Triangle triangle2{
        {300, 700}, {800, 500}, {400, 400}, 
        {0, 0, 0, 0}, false
    };

    sgf::gui::Rectangle rectangle{
        {100, 200}, {200, 200}, {100, 100}, {200, 100},
        {200, 250, 120, 0}, false
    };
};