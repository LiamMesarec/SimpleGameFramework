#include "../../include/engine/SceneManager.hpp"
#include "../../include/engine/Window.hpp"
#include "../../include/engine/Camera.hpp"
#include "../../include/engine/Engine.hpp"
#include "../../include/engine/Time.hpp"
#include <iostream>

namespace sgf
{
    SceneManager::SceneManager() noexcept
    {
        
    }

    SceneManager::~SceneManager() 
    {
        scenes.clear();
    }
    
    void SceneManager::OpenScene(std::shared_ptr<Scene> scene) 
    {
        if(GetCurrentScene()) 
        {
            scenes.pop_back();
        }
        
        scenes.push_back(scene);
    }

    std::shared_ptr<Scene> SceneManager::GetCurrentScene() const
    {
        return scenes.empty() ? nullptr : scenes.back();
    }

    void SceneManager::Loop() 
    {
        while(true) 
        {
            FPS::Start();

            if (!GetCurrentScene())
            {
                continue;
            }

            Camera::RenderWithCamera();
            
            SDL_SetRenderDrawColor(Engine::renderer,  
                Window::GetBackgroundColor().r, 
                Window::GetBackgroundColor().g,
                Window::GetBackgroundColor().b,
                Window::GetBackgroundColor().a
            );

            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

            SDL_RenderClear(Engine::renderer);

            GetCurrentScene()->HandleInput();

            GetCurrentScene()->Update();

            //Draw::Start();
            GetCurrentScene()->Render();
            //Draw::End();
            
            SDL_RenderSetScale(Engine::renderer, 1, 1);
            
            SDL_SetRenderTarget(Engine::renderer, NULL);

            Camera::RenderScene();

            SDL_RenderPresent(Engine::renderer);

            FPS::Wait();
        }
    }
}