#include "MoveManager.h"
#include <memory>
#include "../components/PositionComponent.h"
#include "../components/VectorComponent.h"
#include "../components/ObjectidComponent.h"
#include "../entitys/BallEntity.h"
#include "../../Common/include/zmq/cppzmq/zmq_addon.hpp"
#include "singleton/EnvironmentInfo.h"
#include "../Server/singleton/SendBuffDispatch.h"
#include "./include/proto/Ball.pb.h"


extern bool ProtoBuildUpdate(const int64_t&, entt::registry&);
extern bool ProtoBuildInit(entt::registry&);

bool ProtoBuildInit(entt::registry& reg_) {
    LogInfo << "ProtoBuildInit" << FlushLog;
    return true;
}
bool ProtoBuildUpdate(const int64_t& dt_, entt::registry& reg_) {
    BallUpdateEvent _update_event;
    auto _view = reg_.view<BallTag, PositionComponent, ObjectidComponent>();
    _update_event.set_size(static_cast<uint32_t>(_view.size()));
    for (auto _entity_it : _view) {
        Ball* _ball = _update_event.add_ball();
        _ball->set_oid(_view.get<ObjectidComponent>(_entity_it).oid);
        auto _pos = _view.get<PositionComponent>(_entity_it);
        _ball->set_x(_pos.x);
        _ball->set_y(_pos.y);
    }
    std::shared_ptr<std::string> _buff_str(new std::string);
    _update_event.SerializePartialToString(&*_buff_str);
    Singleton<SendBuffDispatch>::getInstance()->pushBuff(_buff_str);
    return true;
}

MgrRegHelper(ProtoBuild) {
    SYSMGR->regInitSys(ProtoBuildInit);
    SYSMGR->regSys(SystemLevel::NORMAl, ProtoBuildUpdate);
}
