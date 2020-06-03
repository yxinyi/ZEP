#include <cstdint>
#include <iostream>
#include <stdio.h>
#include "include/zmq/cppzmq/zmq_addon.hpp"
#include "singleton/EnvironmentInfo.h"
#include "include/tool/Time.h"
#include "include/tool/Timer.h"
#include "include/tool/LogInfo.h"
#include "../BaseEngine/systems/SystemManager.h"
#include "../Server/components/PositionComponent.h"


void MainLoop() {

    try{
        const float _one_frame_time = 1000.f / static_cast<float>(ENV->m_frame);
        Timer _frame_timer;
        Timer _tick_timer;
        while (ENV->m_open) {
            const int64_t _this_frame_time = _frame_timer.elapsed();
            if (_this_frame_time >= _one_frame_time) {
                _tick_timer.reset();
                SYSMGR->loop(_this_frame_time, ENV->m_registry);
                _frame_timer.reset();
                
                int64_t _tick_time = _tick_timer.elapsed();
                if (_tick_time > 150) {
                    if (_tick_time > 300) {
                        LogError << "frame tick :  " << _tick_timer.elapsed() << "entity size: " << ENV->m_registry.size() << FlushLog;
                    }
                    else {
                        LogWarn << "frame tick :  " << _tick_timer.elapsed() << "entity size: " << ENV->m_registry.size() << FlushLog;
                    }
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
    return  0;
}