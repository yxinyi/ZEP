#pragma once
#include <cstdint>
#include <iostream>
#include "tool/SingletonTemplate.h"
#include <unordered_map>
#include "entt.hpp"
#include "google/protobuf/message.h"
#include "include/zmq/cppzmq/zmq_addon.hpp"


class SocketCpt {
public:
    std::shared_ptr<zmq::socket_t> socket;
};

class RecvSocket {
public:
};

class SendSocket {
public:
};

class NewConnectCpt {
public:
};
class RouteIDCpt {
public:
    std::string route_id;
};
class ShakeHandTmCpt {
public:
    uint32_t last_connect_time;
};
class ConnectCpt {
public:
    uint32_t last_connect_time;
    std::vector<std::shared_ptr<google::protobuf::Message>> msg_list;
};



