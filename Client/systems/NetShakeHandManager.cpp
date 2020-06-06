#include <functional>
#include "include/entt.hpp"
#include "include/tool/ManagerInitHelper.h"
#include "include/tool/LogInfo.h"
#include "systems/SystemManager.h"
#include "singleton/EnvironmentInfo.h"
#include "include/proto/Shakehand.pb.h"
#include "singleton/NetInfo.h"
#include "components/NetConnectComponent.h"

using namespace google::protobuf;
bool ShakehandInit(entt::registry& reg_) {

    return true;
}
bool ShakehandUpdate(const int64_t& dt_, entt::registry& reg_) {
    static int64_t _shake_hand_tm = 0;
    static int64_t _first_shakehand = 1;
    _shake_hand_tm += dt_;
    if (_shake_hand_tm > ENV->m_shakehand_tm * 1000 || _first_shakehand == 1) {
        _shake_hand_tm = 0;
        entt::entity _entity =  NetConnect["Shakehand"];
        auto& _msg_list = reg_.get<ConnectCpt>(_entity);
        std::shared_ptr<ShakeHandEvent> _shakehand(new ShakeHandEvent());
        _shakehand->set_state(_first_shakehand);
        _msg_list.msg_list.push_back(_shakehand);
        _first_shakehand = 2;
    }
    return true;
}

MgrRegHelper(ShakeHand) {
    SYSMGR->regInitSys(ShakehandInit);
    SYSMGR->regSys(SystemLevel::NORMAl, ShakehandUpdate);
}

