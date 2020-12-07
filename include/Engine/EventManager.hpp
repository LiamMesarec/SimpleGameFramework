#pragma once
#include <SDL2/SDL.h>

namespace sgf
{
    enum EventType
    {
        KeyPressed = SDL_KEYDOWN, 
        KeyReleased = SDL_KEYUP, 
        MouseMoved = SDL_MOUSEMOTION,
        MousePressed = SDL_MOUSEBUTTONDOWN,
        MouseReleased = SDL_MOUSEBUTTONUP,
        MouseWheelMoved = SDL_MOUSEWHEEL,
        Quit
    };

    enum Key
    {
        Unknown = SDLK_UNKNOWN,
        Backspace = SDLK_BACKSPACE,
        Tab = SDLK_TAB,
        Return = SDLK_RETURN,
        Escape = SDLK_ESCAPE,
        Space = SDLK_SPACE,
        Exclaim = SDLK_EXCLAIM,
        DoubleQuote = SDLK_QUOTEDBL,
        Hash = SDLK_HASH,
        Dollar = SDLK_DOLLAR,
        Percent = SDLK_PERCENT,
        Ampersand = SDLK_AMPERSAND,
        SingleQuote = SDLK_QUOTE,
        LeftParentheses = SDLK_LEFTPAREN,
        RightParantheses = SDLK_RIGHTPAREN
    };

    enum Mouse
    {
        LeftClick,
        RightClick
    };

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