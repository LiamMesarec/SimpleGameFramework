#pragma once
#include <SDL2/SDL.h>
#include "Window.hpp"
#include "SceneManager.hpp"

namespace sgf
{
    class Camera 
    {
    public:
        static void SetCameraSize(int width, int height);
        static void SetSceneSize(int width, int height);
        static void SetZoomLevel(float zoom);
        static void SetPosition(float x, float y);
        static void Move(float x, float y);

        static SDL_Rect& GetCamera();
        static SDL_Rect& GetSceneDimensions();

        static void RenderWithCamera();
        static void RenderScene();
    private:
        inline static SDL_Rect m_camera {0, 0, 0, 0};
        inline static SDL_Rect m_sceneDimensions {0, 0, 0, 0};

        inline static int m_startingWidth = 0;
        inline static int m_startingHeight = 0;

        inline static SDL_Texture* m_screen = nullptr;
    };
}