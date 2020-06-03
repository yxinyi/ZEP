#pragma once
#include "SendBuffDispatch.h"

void SendBuffDispatch::pushBuff(std::shared_ptr<std::string> buf_) {
    m_buffs.push_back(buf_);
}
SendBuffDispatch::SendBuffDispatch() {}

void SendBuffDispatch::foreach(std::function<void(BuffArr&)> func_) {
    func_(m_buffs);
}
