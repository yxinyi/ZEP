#include "BallMoveManager.h"
#include "components/PositionComponent.h"
#include "components/VectorComponent.h"
#include "components/ObjectidComponent.h"
#include "entitys/BallEntity.h"
#include "singleton/GameConfigSingle.h"


bool MoveMgrInit(entt::registry& reg_) {
    return true;
}
bool MoveMgrUpdate(const int64_t& dt_, entt::registry& reg_) {
    auto _view = reg_.view<BallTag, VectorChange,PositionComponent, VectorComponent>();
    for (auto _en_it : _view) {
        auto& _pos = _view.get<PositionComponent>(_en_it);
        auto& _vec = _view.get<VectorComponent>(_en_it);
        _pos.x += static_cast<double>(_vec.x * dt_) / 1000.f;
        _pos.y += static_cast<double>(_vec.y * dt_) / 1000.f;
        //LogInfo << "pos x: " << _pos.x << "pos y: " << _pos.y << FlushLog;
        if (_pos.x >= GameConfig->_windows_x || _pos.x <= 0) {
            auto& _change = _view.get<VectorChange>(_en_it);
            _change.is_change = true;
            _vec.x = -_vec.x;
        }
        if (_pos.y >= GameConfig->_windows_y || _pos.y <= 0) {
            auto& _change = _view.get<VectorChange>(_en_it);
            _change.is_change = true;
            _vec.y = -_vec.y;
        }

    }
    
    return true;
}

MgrRegHelper(BallMoveMgr) {
    SYSMGR->regInitSys(MoveMgrInit);
    SYSMGR->regSys(SystemLevel::NORMAl, MoveMgrUpdate);
}
