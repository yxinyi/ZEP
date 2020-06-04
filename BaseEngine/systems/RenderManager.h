#pragma once
#include <functional>
#include "include/tool/SingletonTemplate.h"
#include "include/entt.hpp"
#include "include/tool/LogInfo.h"
#include "singleton/GameWindow.h"
#include "SDL2/SDL_render.h"


using RenderFunc = std::function<bool(SDL_Renderer*,SDL_Window*, entt::registry&)>;

class RenderManager {
    friend class Singleton<RenderManager>;
public:
    void regRenderFunc(RenderFunc&& func_) {
        m_render_pool.push_back(std::forward<RenderFunc>(func_));
    }
    void loop(entt::registry& registry_) {

        SDL_SetRenderDrawColor(WindowInfo->m_render, 0, 0, 0, 255);
        SDL_RenderClear(WindowInfo->m_render);
        SDL_Renderer* _render = WindowInfo->m_render;
        SDL_Window* _windiow = WindowInfo->m_window;
        if (!_render || !_windiow) {
            LogError << "error " << FlushLog;
            return;
        }
        for (auto& _func_it : m_render_pool) {
            _func_it(_render, _windiow, registry_);
        }
        SDL_RenderPresent(WindowInfo->m_render);
    }
    ~RenderManager()=default;

private:
    RenderManager() {};
    std::vector<RenderFunc> m_render_pool;
};

#define RenderMgr Singleton<RenderManager>::getInstance()