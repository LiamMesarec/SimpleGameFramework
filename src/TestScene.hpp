#pragma once
#include "SGF/Core.hpp"
#include "SGF/Gui.hpp"
#include "SGF/Math.hpp"
#include "Scene2.hpp"

class TestScene : public sgf::Scene 
{
public:
    explicit TestScene(sgf::SceneManagerPtr scene);
    virtual ~TestScene();

    void Render() override;
    void Update() override;
    void HandleInput() override;

private:
    sgf::Polygon polygon {
        sgf::Vertex{50, 500}, sgf::Vertex{150, 500}, sgf::Vertex{150, 600}, sgf::Vertex{50, 600}
    };

    sgf::Polygon trikotnik {
        sgf::Vertex{600, 500}, sgf::Vertex{800, 500}, sgf::Vertex{750, 600}
    };
    
    sgf::Polygon polygon2 {
        sgf::Vertex{200, 200}, sgf::Vertex{500, 200}, sgf::Vertex{400, 400}, sgf::Vertex{200, 400}
    };

    sgf::Polygon desno {
        sgf::Vertex{100, 200}, sgf::Vertex{300, 200}, sgf::Vertex{400, 150}, 
        sgf::Vertex{300, 100}, sgf::Vertex{100, 100}, sgf::Vertex{200, 150}
    };
};