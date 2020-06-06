#include <memory>
#include "components/NetConnectComponent.h"
#include "entitys/BallEntity.h"
#include "include/zmq/cppzmq/zmq_addon.hpp"
#include "singleton/EnvironmentInfo.h"
#include "singleton/NetInfo.h"
#include "singleton/SendBuffDispatch.h"
#include "include/proto/Ball.pb.h"
#include "include/proto/Shakehand.pb.h"
#include "NetConnectManager.h"
#include "include/tool/ManagerInitHelper.h"
#include "include/tool/LogInfo.h"
#include <fstream>

bool NetworkConnectInit(entt::registry& reg_) {
    auto _entity = reg_.create();
    reg_.emplace<SocketCpt>(_entity, std::shared_ptr<zmq::socket_t>(new zmq::socket_t(NetInfo->m_context, zmq::socket_type::dealer)));
    reg_.emplace<ConnectCpt>(_entity);
    reg_.emplace<RouteIDCpt>(_entity, "");
    reg_.emplace<SendSocket>(_entity);
    std::shared_ptr<zmq::socket_t> _sock = reg_.get<SocketCpt>(_entity).socket;

    std::ifstream _infile;
    std::string _buff_str;
    _infile.open("connect_ip.txt", std::ios::in);
    assert(_infile.is_open());
    while (getline(_infile, _buff_str))
    {
    }
    _sock->connect("tcp://"+ _buff_str +":7000");


    NetConnect["MainSocket"] = _entity;
    NetConnect["Shakehand"] = _entity;
    LogInfo << "NetInit" << FlushLog;
    return true;
}
bool NetworkConnectUpdate(const int64_t& dt_, entt::registry& reg_) {

    return true;
}

MgrRegHelper(NetworkConnect) {
    SYSMGR->regInitSys(NetworkConnectInit);
    SYSMGR->regSys(SystemLevel::NORMAl, NetworkConnectUpdate);
}
