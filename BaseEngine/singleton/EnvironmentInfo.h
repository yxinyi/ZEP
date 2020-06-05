#pragma once
#include <cstdint>
#include <iostream>
#include "tool/SingletonTemplate.h"
#include "entt.hpp"
#include "include/zmq/cppzmq/zmq_addon.hpp"

class EnvironmentInfo  {
public:
    const size_t m_frame = 100;
    entt::registry m_registry;
    bool m_open = true;
};

#define ENV Singleton<EnvironmentInfo>::getInstance()