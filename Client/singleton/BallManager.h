#pragma once
#include <cstdint>
#include <iostream>
#include "tool/SingletonTemplate.h"
#include "entt.hpp"
#include "include/zmq/cppzmq/zmq_addon.hpp"
#include <unordered_map>
class BallManager  {
public:
    std::unordered_map<uint64_t, entt::entity> m_ball_pool;
};

#define BallMgr Singleton<BallManager>::getInstance()->m_ball_pool