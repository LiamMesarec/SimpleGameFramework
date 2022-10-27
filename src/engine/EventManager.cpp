#include "engine/EventManager.hpp"

namespace sgf 
{
    bool EventManager::EventLoop()
    {
        int event = SDL_PollEvent(&m_event);
        
        Event = static_cast<EventType>(m_event.type);
        ActiveKey = static_cast<Key>(m_event.key.keysym.sym);

        return static_cast<bool>(event);
    }
}
