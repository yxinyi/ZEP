#include <memory>
#include "components/NetConnectComponent.h"
#include "NetConnectManager.h"
#include "singleton/EnvironmentInfo.h"
#include "singleton/NetInfo.h"
#include "singleton/ProtobufDispatcher.h"
#include "singleton/ProtobufCodec.h"
#include "systems/SystemManager.h"
#include "include/zmq/cppzmq/zmq_addon.hpp"
#include "include//tool/Time.h"
#include "include/proto/Shakehand.pb.h"
#include "include/tool/ManagerInitHelper.h"
#include "include/tool/SingletonTemplate.h"
#include "include/tool/LogInfo.h"


bool ShakehandManagerInit(entt::registry& reg_) {
    EventRegister(ShakeHandEvent, [&reg_](std::shared_ptr<zmq::socket_t> socket_, const std::shared_ptr<ShakeHandEvent>& message_, const int64_t& tm_,const string& route_id_) {

        const uint32_t _state = message_->state();

        //第一次连接
        if (_state == 1) {
            if (NetConnect.find(route_id_) != NetConnect.end()) {
                LogInfo << "the route id" << route_id_ << "relogin" << FlushLog;
            }
            auto _entity = reg_.create();
            reg_.emplace<SocketCpt>(_entity, socket_);
            reg_.emplace<NewConnectCpt>(_entity);
            reg_.emplace<ConnectCpt>(_entity);
            reg_.emplace<ShakeHandTmCpt>(_entity, static_cast<uint32_t>(Time::getInstance()->Now()));
            reg_.emplace<RouteIDCpt>(_entity, route_id_);

            NetConnect[route_id_] = _entity;
        }
        else {
            if (NetConnect.find(route_id_) == NetConnect.end()) {
                LogInfo << "the route id" << route_id_ << "not login" << FlushLog;
                return;
            }
            auto _entity = NetConnect[route_id_];
            auto& _connect = reg_.get<ShakeHandTmCpt>(_entity);
            _connect.last_connect_time = static_cast<uint32_t>(Time::getInstance()->Now());
        }
    });
    LogInfo << "ShakehandManagerInit" << FlushLog;

    return true;
}
bool ShakehandManagerUpdate(const int64_t& dt_, entt::registry& reg_) {
    auto _view = reg_.view<ShakeHandTmCpt, RouteIDCpt>();
    std::vector<entt::entity> _destory_vec;
    uint64_t _now_time = Time::getInstance()->Now();
    for (auto& _entity_it : _view) {
        auto& _connect = _view.get<ShakeHandTmCpt>(_entity_it);
        if ((_now_time - _connect.last_connect_time) > (ENV->m_shakehand_tm * 2)) {
            auto& _rout_id = _view.get<RouteIDCpt>(_entity_it);
            NetConnect.erase(_rout_id.route_id);
            _destory_vec.push_back(_entity_it);
        }
    }
    for (auto& _des_it : _destory_vec) {
        reg_.destroy(_des_it);
    }
    return true;
}

MgrRegHelper(Shakehand) {
    SYSMGR->regInitSys(ShakehandManagerInit);
    SYSMGR->regSys(SystemLevel::NORMAl, ShakehandManagerUpdate);
}
