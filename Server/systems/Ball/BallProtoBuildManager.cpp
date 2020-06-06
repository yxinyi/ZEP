#include <memory>
#include "components/PositionComponent.h"
#include "components/VectorComponent.h"
#include "components/ObjectidComponent.h"
#include "components/NetConnectComponent.h"
#include "entitys/BallEntity.h"
#include "include/zmq/cppzmq/zmq_addon.hpp"
#include "singleton/EnvironmentInfo.h"
#include "singleton/SendBuffDispatch.h"
#include "include/proto/Ball.pb.h"


extern bool ProtoBuildUpdate(const int64_t&, entt::registry&);
extern bool ProtoBuildInit(entt::registry&);

bool ProtoBuildInit(entt::registry& reg_) {
    LogInfo << "ProtoBuildInit" << FlushLog;
    return true;
}
bool ProtoBuildUpdate(const int64_t& dt_, entt::registry& reg_) {

    //如果是新连接,先进行全同步
    if (reg_.view<NewConnectCpt>().size()) {
        std::shared_ptr<BallUpdateEvent> _all_update_event(new BallUpdateEvent());
        auto _view = reg_.view<BallTag, VectorComponent, PositionComponent, ObjectidComponent>();
        _all_update_event->set_size(_view.size());
        for (auto _entity_it : _view) {
            Ball* _ball = _all_update_event->add_ball();
            _ball->set_oid(_view.get<ObjectidComponent>(_entity_it).oid);
            auto _pos = _view.get<PositionComponent>(_entity_it);
            _ball->set_x(_pos.x);
            _ball->set_y(_pos.y);
            auto _vector = _view.get<VectorComponent>(_entity_it);
            _ball->set_vector_x(_vector.x);
            _ball->set_vector_y(_vector.y);
        }

        //向所有新连接进行消息传播
        auto _new_connect_view = reg_.view<NewConnectCpt, ConnectCpt>();
        for (auto& _new_connect_it : _new_connect_view) {
            LogInfo << "new connect all update" << FlushLog;
            auto& _connect_msg = _new_connect_view.get<ConnectCpt>(_new_connect_it);
            _connect_msg.msg_list.push_back(_all_update_event);
            reg_.remove_if_exists<NewConnectCpt>(_new_connect_it);
        }
    }
    
    //如果有向量变化进行校正
    if (reg_.view<VectorChange>().size()) {
        std::shared_ptr<BallUpdateEvent> _update_event(new BallUpdateEvent());
        auto _view = reg_.view<BallTag, VectorChange, VectorComponent, PositionComponent, ObjectidComponent>();

        int _change_node = 0;
        for (auto _entity_it : _view) {
            auto& _change = _view.get<VectorChange>(_entity_it);
            if (_change.is_change == false) {
                continue;
            }
            _change.is_change = false;
            _change_node++;
            Ball* _ball = _update_event->add_ball();
            _ball->set_oid(_view.get<ObjectidComponent>(_entity_it).oid);
            auto _pos = _view.get<PositionComponent>(_entity_it);
            _ball->set_x(_pos.x);
            _ball->set_y(_pos.y);
            auto _vector = _view.get<VectorComponent>(_entity_it);
            _ball->set_vector_x(_vector.x);
            _ball->set_vector_y(_vector.y);
        }
        _update_event->set_size(_change_node);

        //向所有连接进行传播
        auto _new_connect_view = reg_.view< ConnectCpt>();
        for (auto& _connect_it : _new_connect_view) {
            auto& _connect_msg = _new_connect_view.get<ConnectCpt>(_connect_it);
            _connect_msg.msg_list.push_back(_update_event);
        }

    }
    return true;
}

MgrRegHelper(ProtoBuild) {
    SYSMGR->regInitSys(ProtoBuildInit);
    SYSMGR->regSys(SystemLevel::NORMAl, ProtoBuildUpdate);
}
