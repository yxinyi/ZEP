#include <memory>
#include "components/PositionComponent.h"
#include "components/VectorComponent.h"
#include "components/ObjectidComponent.h"
#include "entitys/BallEntity.h"
#include "../../Common/include/zmq/cppzmq/zmq_addon.hpp"
#include "singleton/EnvironmentInfo.h"
#include "singleton/ClientNetInfo.h"
#include "singleton/ProtobufCodec.h"
#include "singleton/ProtobufDispatcher.h"
#include "singleton/BallManager.h"
#include "include/tool/Timer.h"
#include "BallCreateSystem.h"
#include "./proto/Ball.pb.h"

using namespace google::protobuf;
bool BallCreateInit(entt::registry& reg_) {
    EventRegister(BallUpdateEvent,[&reg_](zmq::socket_t& socket_, const std::shared_ptr<BallUpdateEvent>& message_, const int64_t& tm_) {
        const uint32_t _size = message_->size();
        //LogInfo << "EventRegister : " << _size << FlushLog;
        for (size_t _idx = 0; _idx < _size; _idx++) {
            const Ball& _ball = message_->ball(static_cast<int>(_idx));
            const uint64_t _ball_oid = _ball.oid();
            const double _ball_x = _ball.x();
            const double _ball_y = _ball.y();
            const double _ball_vector_x = _ball.vector_x();
            const double _ball_vector_y = _ball.vector_y();
            if (BallMgr.find(_ball_oid) == BallMgr.end()) {
                auto _entity = reg_.create();
                reg_.emplace<BallTag>(_entity);
                reg_.emplace<ObjectidComponent>(_entity, static_cast<uint64_t>(_ball_oid));
                reg_.emplace<PositionComponent>(_entity, _ball_x, _ball_y);
                reg_.emplace<VectorComponent>(_entity, _ball_vector_x, _ball_vector_y);
                BallMgr[_ball_oid] = _entity;
            }
            else {
                PositionComponent& _pos = reg_.get<PositionComponent>(BallMgr[_ball_oid]);
                _pos.x = _ball_x;
                _pos.y = _ball_y;
                VectorComponent& _vector = reg_.get<VectorComponent>(BallMgr[_ball_oid]);
                _vector.x = _ball_vector_x;
                _vector.y = _ball_vector_y;
            }
        }
        //LogInfo << "this fram update : " << _size << FlushLog;
        //LogInfo << "client ball size : " << BallMgr.size() << FlushLog;
    });
    return true;
}
bool BallCreateUpdate(const int64_t& dt_, entt::registry& reg_) {
    return true;
}

MgrRegHelper(BallCreate) {
    SYSMGR->regInitSys(BallCreateInit);
    SYSMGR->regSys(SystemLevel::NORMAl, BallCreateUpdate);
}
