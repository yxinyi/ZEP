#include "MoveManager.h"
#include <memory>
#include "../components/PositionComponent.h"
#include "../components/VectorComponent.h"
#include "../components/ObjectidComponent.h"
#include "../entitys/BallEntity.h"
#include "../../Common/include/zmq/cppzmq/zmq_addon.hpp"
#include "singleton/EnvironmentInfo.h"
#include "singleton/NetInfo.h"
#include "../Server/singleton/SendBuffDispatch.h"
#include "./include/proto/Ball.pb.h"


bool NetInit(entt::registry& reg_) {
    zmq::socket_t _sock(NETINFO->m_context, zmq::socket_type::pub);
    _sock.bind("tcp://127.0.0.1:7000");
    NETINFO->m_pub_socket.swap(_sock);
    LogInfo << "NetInit" << FlushLog;
    return true;
}
bool NetUpdate(const int64_t& dt_, entt::registry& reg_) {
    Singleton<SendBuffDispatch>::getInstance()->foreach([](BuffArr& arr_) {
        for (auto& _buff_it : arr_) {
            NETINFO->m_pub_socket.send(zmq::buffer(*_buff_it), zmq::send_flags::none);
        }
        arr_.clear();
    });

    return true;
}

MgrRegHelper(NetMgr) {
    SYSMGR->regInitSys(NetInit);
    SYSMGR->regSys(SystemLevel::NORMAl, NetUpdate);
}
