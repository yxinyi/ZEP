#include <memory>
#include "components/NetConnectComponent.h"
#include "systems/SystemManager.h"
#include "include/zmq/cppzmq/zmq_addon.hpp"
#include "singleton/EnvironmentInfo.h"
#include "singleton/NetInfo.h"
#include "include/proto/Shakehand.pb.h"
#include "NetConnectManager.h"
#include "singleton/ProtobufCodec.h"
#include "singleton/ProtobufDispatcher.h"

bool NetworkConnectInit(entt::registry& reg_) {
    auto _entity = reg_.create();
    reg_.emplace<SocketCpt>(_entity, std::shared_ptr<zmq::socket_t>(new zmq::socket_t(NetInfo->m_context, zmq::socket_type::router)));
    reg_.emplace<ConnectCpt>(_entity);
    reg_.emplace<RouteIDCpt>(_entity, "MainSocket");
    std::shared_ptr<zmq::socket_t> _sock = reg_.get<SocketCpt>(_entity).socket;
    //_sock.reset(new zmq::socket_t(NetInfo->m_context, zmq::socket_type::router));
    _sock->bind("tcp://127.0.0.1:7000");
    NetConnect["MainSocket"] = _entity;
    return true;
}
bool NetworkConnectUpdate(const int64_t& dt_, entt::registry& reg_) {

    return true;
}

MgrRegHelper(NetworkConnect) {
    SYSMGR->regInitSys(NetworkConnectInit);
    SYSMGR->regSys(SystemLevel::NORMAl, NetworkConnectUpdate);
}
