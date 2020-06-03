#pragma once
#include <cstdint>
#include <iostream>
#include "tool/SingletonTemplate.h"

class GameConfigInfo  {
public:
    uint32_t _windows_x = 1280;
    uint32_t _windows_y = 720;
};

#define GameConfig Singleton<GameConfigInfo>::getInstance()