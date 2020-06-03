#pragma once
#include <cstdint>
#include <iostream>
#include "tool/SingletonTemplate.h"
#include "entt.hpp"
#include "include/zmq/cppzmq/zmq_addon.hpp"
#include "tool/SingletonTemplate.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/message.h"
using namespace google::protobuf;

// muduo module
class ProtobufCodec : public Singleton<ProtobufCodec> {
    friend class Singleton<ProtobufCodec>;
public:
    Message* createMessage(const std::string& proto_name_);
    Message* decode(const std::string& proto_name_, const std::string& zmq_msg_);
private:
    ProtobufCodec() {};
};

#define ProtoCodec Singleton<ProtobufCodec>::getInstance()