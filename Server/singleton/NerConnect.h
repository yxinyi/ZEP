#pragma once
#include <cstdint>
#include <iostream>
#include "tool/SingletonTemplate.h"
#include <unordered_map>
#include "entt.hpp"
#include "../Common/google/protobuf/message.h"

class NewConnect {
public:
};

class Connect {
public:
    std::string m_route_id;
    std::vector<std::shared_ptr<google::protobuf::Message>> m_msg_list;
};
class NetConnect  {
public:
    std::unordered_map<std::string, entt::entity> m_connect_pool;
};

#define NetConnects Singleton<NetConnect>::getInstance()