#include <functional>
#include "include/entt.hpp"
#include "include/tool/ManagerInitHelper.h"
#include "include/tool/SingletonTemplate.h"
#include "../../Common/include/tool/LogInfo.h"
#include "systems/SystemManager.h"
#include "./include/proto/Ball.pb.h"
#include "singleton/EnvironmentInfo.h"

using namespace google::protobuf;
bool ShakeHandUpdate(const int64_t& dt_, entt::registry& reg_) {
    static int64_t _shake_hand_tm = 0;
    _shake_hand_tm += dt_;
    if (_shake_hand_tm > ENV->m_shakehand_tm * 1000) {
        _shake_hand_tm = 0;
    }
    return true;
}

MgrRegHelper(ShakeHand) {
    SYSMGR->regSys(SystemLevel::NORMAl,ShakeHandUpdate);
}

