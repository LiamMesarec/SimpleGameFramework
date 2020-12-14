#include "../../include/engine/Camera.hpp"
#include "../../include/engine/Window.hpp"

namespace sgf
{
    void Camera::Init()
    {
        m_camera.w = Window::GetWidth();
        m_camera.h = Window::GetHeight();
    }

    void Camera::SetCameraSize(int width, int height)
    {
        m_camera.w = width;
        m_camera.h = height;
    }

    void Camera::SetSceneSize(int width, int height)
    {
        m_sceneDimensions.w = width;
        m_sceneDimensions.h = height;
    }

    void Camera::Move(float x, float y)
    {
        if(m_camera.x < m_sceneDimensions.x + x && m_camera.x > 0)
        {
            m_camera.x += x;
        }
        if(m_camera.y < m_sceneDimensions.y + y && m_camera.y > 0)
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
}