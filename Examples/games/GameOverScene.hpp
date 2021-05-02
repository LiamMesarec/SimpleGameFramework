#pragma once
#include "../../include/SGF/Core.hpp"
#include "../../include/SGF/Gui.hpp"
#include "Shared.hpp"

class GameOverScene : public sgf::Scene 
{
public:
    explicit GameOverScene(sgf::SceneManagerPtr scene, Result winFlag, EScene previousScene);
    virtual ~GameOverScene();

    void Render() override;
    void Update() override;
    void HandleInput() override;
private:
    Result m_winFlag;
    EScene m_previousScene;
    sgf::Polygon playAnotherGame{300, 200, 500, 50};
    sgf::Polygon yes{450, 300, 100, 50};
    sgf::Polygon no{450, 400, 100, 50};
    sgf::Polygon quit{450, 500, 100, 50};
};