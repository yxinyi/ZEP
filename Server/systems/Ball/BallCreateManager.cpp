#include "BallMoveManager.h"
#include "components/PositionComponent.h"
#include "components/VectorComponent.h"
#include "components/ObjectIDComponent.h"
#include "entitys/BallEntity.h"
#include "tool/Time.h"
#include "singleton/UniqueNumberFactory.h"

#include<random>  
#include<time.h> 

bool BallCreateInit(entt::registry& reg_) {

    std::default_random_engine _random(time(NULL));
    std::uniform_real_distribution<double> _random_x_range(0.f, 1280.0);
    std::uniform_real_distribution<double> _random_y_range(0.f, 720.0);
    std::uniform_real_distribution<double> _random_speed_x_range(-100.f, 100.f);
    std::uniform_real_distribution<double> _random_speed_y_range(-100.f, 100.f);
    LogInfo << "MoveMgrInit" << FlushLog;
    for (size_t _slot = 0; _slot < 100000;_slot++) {
        auto _entity = reg_.create();
        reg_.emplace<BallTag>(_entity);
        reg_.emplace<VectorChange>(_entity);
        reg_.emplace<ObjectidComponent>(_entity, static_cast<uint64_t>(APIGetUniqueNumber()));
        reg_.emplace<PositionComponent>(_entity, _random_x_range(_random), _random_y_range(_random));
        reg_.emplace<VectorComponent>(_entity, _random_speed_x_range(_random), _random_speed_y_range(_random));
        //reg_.emplace<VectorComponent>(_entity, double(1000), double(1000));
    }

    return true;
}

bool BallCreateUpdate(const int64_t& dt_, entt::registry& reg_) {
    //std::default_random_engine _random(time(NULL));
    //std::uniform_real_distribution<double> _random_x_range(0.f, 1280.0);
    //std::uniform_real_distribution<double> _random_y_range(0.f, 720.0);
    //std::uniform_real_distribution<double> _random_speed_x_range(-100.f, 100.f);
    //std::uniform_real_distribution<double> _random_speed_y_range(-100.f, 100.f);
    //for (size_t _slot = 0; _slot < 20;_slot++) {
    //    auto _entity = reg_.create();
    //    reg_.emplace<BallTag>(_entity);
    //    reg_.emplace<VectorChange>(_entity);
    //    reg_.emplace<ObjectidComponent>(_entity, static_cast<uint64_t>(APIGetUniqueNumber()));
    //    reg_.emplace<PositionComponent>(_entity, _random_x_range(_random), _random_y_range(_random));
    //    reg_.emplace<VectorComponent>(_entity, _random_speed_x_range(_random), _random_speed_y_range(_random));
    //}
    return true;
}

MgrRegHelper(BallCreate) {
    SYSMGR->regInitSys(BallCreateInit);
    SYSMGR->regSys(SystemLevel::BEFORE, BallCreateUpdate);
}
