#include "MoveManager.h"
#include "../components/PositionComponent.h"
#include "../components/VectorComponent.h"
#include "../components/ObjectidComponent.h"
#include "../entitys/BallEntity.h"
#include "../singleton/GameConfigSingle.h"


bool MoveMgrInit(entt::registry& reg_) {
    return true;
}
bool MoveMgrUpdate(const int64_t& dt_, entt::registry& reg_) {
    auto _view = reg_.view<BallTag, PositionComponent, VectorComponent>();
    for (auto _en_it : _view) {
        auto& _pos = _view.get<PositionComponent>(_en_it);
        auto& _vec = _view.get<VectorComponent>(_en_it);
        _pos.x += _vec.x;
        _pos.y += _vec.y;
    }
    
    return true;
}

MgrRegHelper(MoveMgr) {
    SYSMGR->regInitSys(MoveMgrInit);
    SYSMGR->regSys(SystemLevel::NORMAl, MoveMgrUpdate);
}
