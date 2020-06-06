#include <memory>
#include "../components/PositionComponent.h"
#include "../components/VectorComponent.h"
#include "../components/ObjectidComponent.h"
#include "../entitys/BallEntity.h"
#include "../../Common/include/zmq/cppzmq/zmq_addon.hpp"
#include "singleton/EnvironmentInfo.h"
#include "singleton/NetInfo.h"
#include "../Server/singleton/SendBuffDispatch.h"
#include "./include/proto/Ball.pb.h"
#include "NetConnectManager.h"


bool NetworkConnectInit(entt::registry& reg_) {

    return true;
}
bool NetworkConnectUpdate(const int64_t& dt_, entt::registry& reg_) {

    return true;
}

MgrRegHelper(NetworkConnect) {
    SYSMGR->regInitSys(NetworkConnectInit);
    SYSMGR->regSys(SystemLevel::NORMAl, NetworkConnectUpdate);
}
