#include "../../include/engine/SceneManager.hpp"
#include "../../include/engine/Window.hpp"
#include "../../include/engine/Camera.hpp"
#include "../../include/engine/Engine.hpp"
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
        m_screen = nullptr;
        m_screen = SDL_CreateTexture(Engine::renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 
            5000, 5000);

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
            if (!GetCurrentScene())
            {
                continue;
            }

            SDL_SetRenderTarget(Engine::renderer, m_screen);
            
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

            GetCurrentScene()->Render();

            SDL_RenderSetScale(Engine::renderer, 1, 1);
            
            SDL_SetRenderTarget(Engine::renderer, NULL);


            SDL_RenderCopy(Engine::renderer, m_screen, &Camera::GetSceneDimensions(), &Camera::GetCamera());

            SDL_RenderPresent(Engine::renderer);

            //TODO: Chrono za SDL_Delay
            SDL_Delay(25);
        }
    }
}