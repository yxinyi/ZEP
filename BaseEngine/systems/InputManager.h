#pragma once
#include <functional>
#include "include/tool/SingletonTemplate.h"
#include "include/entt.hpp"
#include "singleton/GameWindow.h"

class InputManager {
    friend class Singleton<InputManager>;
public:

    void loop() {
        while (SDL_PollEvent(&WindowInfo->m_event) != 0)
        {
            switch (WindowInfo->m_event.type)
            {
            case SDL_QUIT:
                //m_window.m_isOpen = false;
                break;

            case SDL_KEYDOWN:
                //switch (m_window.m_event.key.keysym.sym)
                //{
                //case SDLK_ESCAPE:
                //    m_window.m_isOpen = false;
                //    break;
                //}
                break;
            }

            // Process system events.
            //m_moveSystem.event(m_window.m_event, m_registry);
        }
    }
    ~InputManager() = default;

private:
    InputManager() {}
};

#define InputMgr Singleton<InputManager>::getInstance()