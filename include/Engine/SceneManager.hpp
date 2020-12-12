#pragma once
#include <memory>
#include <vector>
#include "Scene.hpp"
#include <SDL2/SDL.h>

namespace sgf
{
    class SceneManager
    {
    public:
        SceneManager() noexcept;
        virtual ~SceneManager();

        void OpenScene(std::shared_ptr<Scene> scene);
        std::shared_ptr<Scene> GetCurrentScene() const;
        void Loop();

    private:
        SDL_Texture* m_screen;
        std::vector<std::shared_ptr<Scene>> scenes;
    };
}