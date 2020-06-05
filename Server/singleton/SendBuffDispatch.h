#pragma once
#include <cstdint>
#include <iostream>
#include "tool/SingletonTemplate.h"
#include <memory>
#include <functional>
#include <vector>
#include <google/protobuf/message.h>

using BuffArr = std::vector<std::shared_ptr<google::protobuf::Message>>;
class SendBuffDispatch :public Singleton<SendBuffDispatch> {
    friend class Singleton<SendBuffDispatch>;
public:
    void pushBuff(std::shared_ptr<google::protobuf::Message> buf_) {
        m_buffs.push_back(buf_);
    }
    void foreach(std::function<void (BuffArr&)> func_) {
        func_(m_buffs);
    }
    BuffArr m_buffs;
private:
    SendBuffDispatch() {};
};
