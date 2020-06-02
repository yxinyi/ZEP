#include "MoveManager.h"
#include "../components/PositionComponent.h"
#include "../components/VectorComponent.h"
#include "../components/ObjectIDComponent.h"
#include "../entitys/BallEntity.h"
#include "tool/Time.h"
#include "singleton/UniqueNumberFactory.h"


bool BallCreateInit(entt::registry& reg_) {
    LogInfo << "MoveMgrInit" << FlushLog;
    for (size_t _slot = 0; _slot < 1000;_slot++) {
        auto _entity = reg_.create();
        reg_.emplace<BallTag>(_entity);
        reg_.emplace<ObjectidComponent>(_entity, static_cast<uint64_t>(APIGetUniqueNumber()));
        reg_.emplace<PositionComponent>(_entity, 10.f, 20.f);
        reg_.emplace<VectorComponent>(_entity, 10.f, 20.f);
    }
    return true;
}
bool BallCreateUpdate(const int64_t& dt_, entt::registry& reg_) {
    for (size_t _slot = 0; _slot < 10; _slot++) {
        auto _entity = reg_.create();
        reg_.emplace<BallTag>(_entity);
        reg_.emplace<ObjectidComponent>(_entity, static_cast<uint64_t>(APIGetUniqueNumber()));
        reg_.emplace<PositionComponent>(_entity, 10.f, 20.f);
        reg_.emplace<VectorComponent>(_entity, 10.f, 20.f);
    }
    //auto _view = reg_.view<PositionComponent>();
    //for (auto _entity_it : _view) {
    //    auto& _pos = _view.get<PositionComponent>(_entity_it);
    //    LogInfo << "BallCreateUpdate:  x: " << _pos.x << "  y:  " << _pos.y << FlushLog;
    //}
    return true;
}

MgrRegHelper(BallCreate) {
    SYSMGR->regInitSys(BallCreateInit);
    SYSMGR->regSys(SystemLevel::BEFORE, BallCreateUpdate);
}
