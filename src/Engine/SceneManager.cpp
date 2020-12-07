#include "../../include/engine/SceneManager.hpp"
#include "../../include/engine/Window.hpp"

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
        while(true) 
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

            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

            SDL_RenderClear(renderer);

            GetCurrentScene()->HandleInput();

            GetCurrentScene()->Update();

            GetCurrentScene()->Render();

            SDL_RenderSetScale(renderer, 1, 1);

            SDL_RenderPresent(renderer);

            //TODO: Chrono za SDL_Delay
            SDL_Delay(25);
        }
    }
}