#pragma once
#include <cstdint>
#include <iostream>
#include "include/tool/SingletonTemplate.h"
#include "entt.hpp"
#include "include/zmq/cppzmq/zmq_addon.hpp"

class UniqueNumberFactory : public Singleton<UniqueNumberFactory> {
    friend Singleton<UniqueNumberFactory>;
private:
    UniqueNumberFactory();
public:
    uint64_t build();
};

uint64_t APIGetUniqueNumber();
