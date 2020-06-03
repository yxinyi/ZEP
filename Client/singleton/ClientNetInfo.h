#pragma once
#include <cstdint>
#include <iostream>
#include "tool/SingletonTemplate.h"
#include "entt.hpp"
#include "include/zmq/cppzmq/zmq_addon.hpp"

class NetInfo  {
public:
    zmq::context_t m_context;
    zmq::socket_t m_sub_socket;
};

#define NETINFO Singleton<NetInfo>::getInstance()