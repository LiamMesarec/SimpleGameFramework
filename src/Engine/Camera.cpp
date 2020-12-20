#include "../../include/engine/Camera.hpp"
#include "../../include/engine/Window.hpp"
#include "../../include/engine/Engine.hpp"

namespace sgf
{
    void Camera::SetCameraSize(int width, int height)
    {
        m_camera.w = width;
        m_camera.h = height;
        m_startingWidth = m_camera.w;
        m_startingHeight = m_camera.h;
    }

    void Camera::SetSceneSize(int width, int height)
    {
        m_sceneDimensions.w = width;
        m_sceneDimensions.h = height;

        m_screen = SDL_CreateTexture(Engine::renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 
            m_sceneDimensions.w, m_sceneDimensions.h);
    }

    void Camera::Move(float x, float y)
    {
        if(m_camera.x < m_sceneDimensions.w - m_camera.w && m_camera.x >= 0)
        {
            m_camera.x += x;
        }
        if(m_camera.y < m_sceneDimensions.h - m_camera.h && m_camera.y >= 0)
        {
            m_camera.y += y;
        }        
    }

    void Camera::SetZoomLevel(float zoom)
    {
        m_camera.h = zoom * m_startingWidth;
        m_camera.w = zoom * m_startingHeight;
    }

    void Camera::SetPosition(float x, float y)
    {
        m_camera.x = x;
        m_camera.y = y;
    }

    SDL_Rect& Camera::GetCamera()
    {
        return m_camera;
    }

    SDL_Rect& Camera::GetSceneDimensions()
    {
        return m_sceneDimensions;
    }

    void Camera::RenderWithCamera()
    {
        SDL_SetRenderTarget(Engine::renderer, m_screen);
    }

    void Camera::RenderScene()
    {
        SDL_RenderCopy(Engine::renderer, m_screen, &m_camera, &m_sceneDimensions);
    }
}