#pragma once
#include <cstdint>
#include <iostream>
#include "tool/SingletonTemplate.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_events.h"

class GameWindowInfo {
public:
    SDL_Renderer* m_render;
    SDL_Window* m_window;
    SDL_Event m_event;
};

#define WindowInfo Singleton<GameWindowInfo>::getInstance()