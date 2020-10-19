#pragma once
#include <memory>
#include "SceneManager.hpp"

namespace sgf
{
    class SceneManager;
    using SceneManagerPtr = std::shared_ptr<SceneManager>;
    
    class Scene
    {
    public:
        virtual void Render() = 0;
        virtual void Update() = 0;
        virtual void HandleInput() = 0;
    protected:
	    SceneManagerPtr scene;
    };
}