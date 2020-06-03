#pragma once
#include <cstdint>
#include <iostream>
#include "tool/SingletonTemplate.h"
#include <memory>
#include <functional>
#include <vector>

using BuffArr = std::vector<std::shared_ptr<std::string>>;
class SendBuffDispatch :public Singleton<SendBuffDispatch> {
    friend class Singleton<SendBuffDispatch>;
public:
    void pushBuff(std::shared_ptr<std::string> buf_);
    void foreach(std::function<void (BuffArr&)>);
    BuffArr m_buffs;
private:
    SendBuffDispatch();
};
