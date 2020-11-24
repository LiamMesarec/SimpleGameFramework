#pragma once
#include "../SGF/Core.hpp"
#include "../SGF/Gui.hpp"

class GameOverScene : public sgf::Scene 
{
public:
    explicit GameOverScene(sgf::SceneManagerPtr scene, bool winFlag);
    virtual ~GameOverScene();

    void Render() override;
    void Update() override;
    void HandleInput() override;
private:
    bool m_winFlag;
    sgf::Polygon m_rectangle{sgf::Vertex{100, 200}, sgf::Vertex{800, 200}, sgf::Vertex{800, 500}, sgf::Vertex{100, 500}};
};