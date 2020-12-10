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
        RightParantheses = SDLK_RIGHTPAREN,
        A = SDLK_a,
        B = SDLK_b,
        C = SDLK_c,
        D = SDLK_d,        
        E = SDLK_e,
        F = SDLK_f,
        G = SDLK_g,
        H = SDLK_h,
        I = SDLK_i,        
        J = SDLK_j,
        K = SDLK_k,
        L = SDLK_l,
        M = SDLK_m,
        N = SDLK_n,        
        O = SDLK_o,
        P = SDLK_p,
        Q = SDLK_q,
        R = SDLK_r,
        S = SDLK_s,
        T = SDLK_t,
        U = SDLK_u,        
        V = SDLK_v,
        W = SDLK_w,
        X = SDLK_x,
        Y = SDLK_y,
        Z = SDLK_z,
        _0 = SDLK_0,
        _1 = SDLK_1,
        _2 = SDLK_2,
        _3 = SDLK_3,
        _4 = SDLK_4,
        _5 = SDLK_5,
        _6 = SDLK_6,
        _7 = SDLK_7,
        _8 = SDLK_8,
        _9 = SDLK_9,

    };

    enum Mouse
    {
        LeftClick,
        RightClick
    };    
}