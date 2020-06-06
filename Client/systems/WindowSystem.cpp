#include <memory>
#include "WindowSystem.h"
#include "systems/SystemManager.h"
#include "singleton/GameWindow.h"
#include "include/tool/LogInfo.h"
#include "include/tool/ManagerInitHelper.h"
#include "SDL2/SDL.h"

bool WindowInit(entt::registry& reg_) {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
    {
        std::string message = "Failed to init SDL2! Error: " + std::string(SDL_GetError());
        throw std::runtime_error(message);
    }

    WindowInfo->m_window = SDL_CreateWindow("Ball", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_ALLOW_HIGHDPI);

    if (!WindowInfo->m_window)
    {
        std::string _message = "Window failed to be created! SDL: ";
        _message += SDL_GetError();
        LogError << _message << FlushLog;
    }

    WindowInfo->m_render = SDL_CreateRenderer(WindowInfo->m_window, -1, SDL_RENDERER_SOFTWARE);
    //WindowInfo->m_render = SDL_CreateRenderer(WindowInfo->m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!WindowInfo->m_render)
    {
        std::string _message = "Renderer failed to be created! SDL: ";
        _message += SDL_GetError();
        LogError << _message << FlushLog;
    }

    LogInfo << "WindowInit" << FlushLog;

    return true;
}
bool WindowUpdate(const int64_t& dt_, entt::registry& reg_) {
    return true;
}

MgrRegHelper(Window) {
    SYSMGR->regInitSys(WindowInit);
    SYSMGR->regSys(SystemLevel::NORMAl, WindowUpdate);
}
