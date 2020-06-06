#pragma once
#include <cstdint>
#include <iostream>
#include "tool/SingletonTemplate.h"
#include "entt.hpp"
#include "include/zmq/cppzmq/zmq_addon.hpp"



class NetInfo  {
public:
    zmq::context_t m_context;
};
class NetConnect {
public:
    std::unordered_map<std::string, entt::entity> m_connect_pool;
};


#define NetInfo Singleton<NetInfo>::getInstance()
#define NetConnect Singleton<NetConnect>::getInstance()->m_connect_pool

