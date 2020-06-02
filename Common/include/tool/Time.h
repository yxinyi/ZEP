#pragma once
#include "SingletonTemplate.h"
#include <chrono>
#include <string>

class Time : public Singleton<Time> {
public:
    int64_t Now();
    int64_t NowMillisecond();
    std::string NowStr();
};
