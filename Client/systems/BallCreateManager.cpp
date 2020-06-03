#include <memory>
#include "../components/PositionComponent.h"
#include "../components/VectorComponent.h"
#include "../components/ObjectidComponent.h"
#include "../entitys/BallEntity.h"
#include "../../Common/include/zmq/cppzmq/zmq_addon.hpp"
#include "singleton/EnvironmentInfo.h"
#include "singleton/ClientNetInfo.h"
#include "singleton/ProtobufCodec.h"
#include "singleton/ProtobufDispatcher.h"
#include "BallCreateManager.h"
#include "./proto/Ball.pb.h"

using namespace google::protobuf;
bool BallCreateInit(entt::registry& reg_) {

    EventRegister(BallUpdateEvent,[](zmq::socket_t& socket_, const std::shared_ptr<BallUpdateEvent>& message_, const int64_t& tm_) {
        uint32_t _size = message_->size();
        for (size_t _idx = 0; _idx < _size; _idx++) {
            const Ball& _ball = message_->ball(static_cast<int>(_idx));
            LogInfo << "Ball oid: " << _ball.oid() << " x: " << _ball.x() << " y: " << _ball.y() << FlushLog;
        }
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
