#pragma once
#include <memory>
#include "SceneManager.hpp"
#include <SDL2/SDL.h>
#include "Scene.hpp"
#include "ObjectManager.hpp"

namespace sgf
{
    enum class Resolution
    {
        R_480P, R_720P, R_1080P, R_1440P, R_2160P  
    };

    class Engine 
    {
    public:
        static void CreateWindow(int windowHeight, int windowWidth, const std::string& name);
        static void CreateWindow(Resolution res, const std::string& name);
        static void CloseWindow();

        template<typename T>
        static void OpenScene()
        {   
            ObjectManager::Init();
            m_engine->OpenScene(std::make_unique<T>(m_engine));

            if(!m_loop)
            {
                m_loop = true;
                m_engine->Loop(renderer);
            }
        }

        inline static SDL_Window* window = nullptr;
        inline static SDL_Surface* surface = nullptr;
        inline static SDL_Renderer* renderer = nullptr;

    private:
        inline static std::shared_ptr<SceneManager> m_engine = std::make_shared<SceneManager>();
        inline static bool m_loop = false;
    };
}