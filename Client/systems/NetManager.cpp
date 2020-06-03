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
#include "./include/proto/Ball.pb.h"

using namespace google::protobuf;
bool NetInit(entt::registry& reg_) {
    zmq::socket_t _sock(NETINFO->m_context, zmq::socket_type::sub);
    _sock.connect("tcp://127.0.0.1:7000");
    _sock.set(zmq::sockopt::subscribe, "");
    NETINFO->m_sub_socket.swap(_sock);
    LogInfo << "NetInit" << FlushLog;
    return true;
}
bool NetUpdate(const int64_t& dt_, entt::registry& reg_) {
    zmq::message_t _recv_type_name_msg;
    zmq::message_t _recv_msg;
    if (NETINFO->m_sub_socket.recv(_recv_type_name_msg, zmq::recv_flags::dontwait)) {
        std::string_view _msg_name = _recv_type_name_msg.to_string_view();
        if (_recv_type_name_msg.more()) {
            if (NETINFO->m_sub_socket.recv(_recv_msg, zmq::recv_flags::dontwait)) {
                std::shared_ptr<Message> _msg(ProtoCodec->decode(_recv_type_name_msg.to_string(),_recv_msg.to_string_view()));
                DispatcherEvent(NETINFO->m_sub_socket, _msg, dt_);
            }
        }
        else {
            LogError << "type error" << _recv_type_name_msg << FlushLog;
        }

    }
    return true;
}

MgrRegHelper(NetMgr) {
    SYSMGR->regInitSys(NetInit);
    SYSMGR->regSys(SystemLevel::NORMAl, NetUpdate);
}
