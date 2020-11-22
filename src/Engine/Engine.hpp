#pragma once
#include <memory>
#include "SceneManager.hpp"
#include <SDL2/SDL.h>
#include "Scene.hpp"
#include "ObjectManager.hpp"
#include "../gui/TextureManager.hpp"

namespace sgf
{

    class Engine 
    {
    public:
        template<typename T>
        static void OpenScene()
        {   
            ObjectManager::Init();
            TextureManager::Init();
            m_engine->OpenScene(std::make_unique<T>(m_engine));

            if(!m_loop)
            {
                m_loop = true;
                m_engine->Loop(renderer);
            }
        }

        inline static SDL_Renderer* renderer = nullptr;

    private:
        inline static std::shared_ptr<SceneManager> m_engine = std::make_shared<SceneManager>();
        inline static bool m_loop = false;
    };
}