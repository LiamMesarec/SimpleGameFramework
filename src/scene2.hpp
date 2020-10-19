#pragma once
#include "SGF/Core.hpp"
#include "SGF/Gui.hpp"
#include "SGF/Math.hpp"

class Scene2 : public sgf::Scene 
{
public:
    explicit Scene2(sgf::SceneManagerPtr scene);
    virtual ~Scene2();

    void Render() override;
    void Update() override;
    void HandleInput() override;

private:
    sgf::Polygon polygon {
        sgf::Vertex{200, 200}, sgf::Vertex{1000, 200}, sgf::Vertex{1000, 700}, sgf::Vertex{200, 700}
    };
};