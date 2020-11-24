#include "SceneManager.hpp"
#include "Window.hpp"

namespace sgf
{
    SceneManager::SceneManager() noexcept
    {

    }

    SceneManager::~SceneManager() 
    {
        while (!scenes.empty()) 
        {
            scenes.pop_back();
        }
    }
    
    void SceneManager::OpenScene(std::shared_ptr<Scene> scene) 
    {
        if (GetCurrentScene() != nullptr) 
            scenes.pop_back();
            
        scenes.push_back(scene);
    }

    std::shared_ptr<Scene> SceneManager::GetCurrentScene() const
    {
        return scenes.empty() ? nullptr : scenes.back();
    }

    void SceneManager::Loop(SDL_Renderer* renderer) 
    {
        bool gameLoop = true;

        while(gameLoop) 
        {
            if (GetCurrentScene() == nullptr)
            {
                continue;
            }
            
            SDL_SetRenderDrawColor(renderer, 
                Window::GetBackgroundColor().r, 
                Window::GetBackgroundColor().g,
                Window::GetBackgroundColor().b,
                Window::GetBackgroundColor().a
            );

            SDL_RenderClear(renderer);

            GetCurrentScene()->HandleInput();

            GetCurrentScene()->Update();

            GetCurrentScene()->Render();

            SDL_RenderPresent(renderer);

            //TODO: Chrono za SDL_Delay
            SDL_Delay(25);
        }
    }
}