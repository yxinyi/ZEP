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
#include "../Server/singleton/NerConnect.h"


bool NetInit(entt::registry& reg_) {
    zmq::socket_t _sock(NETINFO->m_context, zmq::socket_type::router);
    _sock.bind("tcp://127.0.0.1:7000");
    NETINFO->m_pub_socket.swap(_sock);
    LogInfo << "NetInit" << FlushLog;
    return true;
}
bool NetUpdate(const int64_t& dt_, entt::registry& reg_) {
    zmq::message_t _recv_type_name_msg;
    zmq::message_t _from_msg;
    if (NETINFO->m_pub_socket.recv(_recv_type_name_msg, zmq::recv_flags::dontwait)) {
        if (_recv_type_name_msg.more()) {
            if (NETINFO->m_pub_socket.recv(_from_msg, zmq::recv_flags::dontwait)) {
                //std::shared_ptr<Message> _msg(ProtoCodec->decode(_recv_type_name_msg.to_string(), _recv_msg.to_string()));
                //DispatcherEvent(NETINFO->m_sub_socket, _msg, dt_);
                const std::string& _target = _from_msg.to_string();
                if (NetConnects->m_connect_pool.find(_target) == NetConnects->m_connect_pool.end()) {
                    //NetConnects->m_connect_pool[_target]
                    auto _entity = reg_.create();
                    reg_.emplace<NewConnect>(_entity);
                    reg_.emplace<Connect>(_entity, _recv_type_name_msg.to_string());
                }
            }
        }
        else {
            LogError << "type error" << _recv_type_name_msg << FlushLog;
        }
    }
    reg_.view<Connect>().each([](auto& connect) {
        for (auto& _msg_it : connect.m_msg_list) {
            LogInfo << "send msg to client: " << connect.m_route_id << FlushLog;
            zmq::send_result_t _route_id_result = NETINFO->m_pub_socket.send(zmq::buffer(connect.m_route_id), zmq::send_flags::sndmore);
            if (_route_id_result == -1) {
                zmq::error_t _err;
                LogInfo << "send error: " << _err.what() << FlushLog;
            }

            static std::string _buff;
            _buff.clear();
            if (_msg_it->SerializeToString(&_buff)) {
                zmq::send_result_t _result = NETINFO->m_pub_socket.send(zmq::buffer(_msg_it->GetTypeName()), zmq::send_flags::sndmore);
                if (_result == -1) {
                    zmq::error_t _err;
                    LogInfo << "send error: " << _err.what() << FlushLog;
                }

                zmq::send_result_t _more_result = NETINFO->m_pub_socket.send(zmq::buffer(_buff), zmq::send_flags::none);
                if (_more_result == -1) {
                    zmq::error_t _err;
                    LogInfo << "send error: " << _err.what() << FlushLog;
                }
            }
        }
        connect.m_msg_list.clear();
    });
    //Singleton<SendBuffDispatch>::getInstance()->foreach([](BuffArr& arr_) {
    //    for (auto& _buff_it : arr_) {
    //        static std::string _buff;
    //        _buff.clear();
    //        if (_buff_it->SerializeToString(&_buff)) {
    //            NETINFO->m_pub_socket.send(zmq::buffer(_buff_it->GetTypeName()), zmq::send_flags::sndmore);
    //            NETINFO->m_pub_socket.send(zmq::buffer(_buff), zmq::send_flags::none);
    //        }
    //    }
    //    arr_.clear();
    //});

    return true;
}

MgrRegHelper(NetMgr) {
    SYSMGR->regInitSys(NetInit);
    SYSMGR->regSys(SystemLevel::NORMAl, NetUpdate);
}
