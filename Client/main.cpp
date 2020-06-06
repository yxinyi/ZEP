#include <cstdint>
#include <stdio.h>
#include "include/entt.hpp"
#include "include/tool/LogInfo.h"
#include "systems/SystemManager.h"
#include "systems/RenderManager.h"
#include "systems/InputManager.h"
#include "include/tool/Timer.h"
#include "singleton/EnvironmentInfo.h"
#include <windows.h>
#include <iostream>




void MainLoop() {
    try {
        const float _one_frame_time = 1000.f / static_cast<float>(ENV->m_frame);
        Timer _frame_timer;
        Timer _tick_timer;
        Timer _second_fps_timer;
        uint32_t _fps_cnt = 1;
        SetConsoleTitleA("client");
        while (ENV->m_open) {
            const int64_t _this_frame_time = _frame_timer.elapsed();
            if (_this_frame_time >= _one_frame_time) {
                _tick_timer.reset();
                _frame_timer.reset();
                SYSMGR->loop(_this_frame_time, ENV->m_registry);

                int64_t _tick_time = _tick_timer.elapsed();
                if (_tick_time > 150) {
                    if (_tick_time > 300) {
                        LogError << "frame tick :  " << _tick_timer.elapsed() << "entity size: " << ENV->m_registry.size() << FlushLog;
                    }
                    else {
                        LogWarn << "frame tick :  " << _tick_timer.elapsed() << "entity size: " << ENV->m_registry.size() << FlushLog;
                    }
                }
                //¿Í»§¶ËÍ¼ÐÎäÖÈ¾
                RenderMgr->loop(ENV->m_registry);
                InputMgr->loop();
                if (_second_fps_timer.elapsed() < 1000) {
                    _fps_cnt ++;
                }
                else {
                    std::string _title = "client fps : ";
                    _title += std::to_string(_fps_cnt);
                    SetConsoleTitleA(_title.c_str());
                    _second_fps_timer.reset();
                    _fps_cnt = 1;
                }
            }

        }
    }
    catch (const std::exception& e)
    {
        LogError << "Exception: " << e.what() << FlushLog;
    }
    catch (...)
    {
        LogError << "Threw an unknown exception. Please derive from std::exception." << FlushLog;
    }
}

int main() {
    SYSMGR->init(ENV->m_registry);
    MainLoop();
    SYSMGR->destory(ENV->m_registry);
    return 0;
}