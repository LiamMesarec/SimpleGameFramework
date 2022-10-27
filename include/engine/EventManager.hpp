#pragma once
#include <SDL2/SDL.h>
#include "Events.hpp"

namespace sgf
{
    class EventManager
    {
    public:
        [[nodiscard]]static bool EventLoop();

        inline static EventType Event;
        inline static Key ActiveKey;
    private:
        static void Quit();

        inline static SDL_Event m_event;
    };
}