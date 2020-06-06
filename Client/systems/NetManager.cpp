#include <memory>
#include "components/PositionComponent.h"
#include "components/VectorComponent.h"
#include "components/ObjectidComponent.h"
#include "components/NetConnectComponent.h"
#include "entitys/BallEntity.h"
#include "include/zmq/cppzmq/zmq_addon.hpp"
#include "singleton/EnvironmentInfo.h"
#include "singleton/NetInfo.h"
#include "singleton/ProtobufDispatcher.h"
#include "singleton/ProtobufCodec.h"
#include "google/protobuf/message.h"




using namespace google::protobuf;
bool NetInit(entt::registry& reg_) {
    return true;
}
bool NetDestory(entt::registry& reg_) {
    reg_.view<SocketCpt>().each([](auto& socket) {
        socket.socket->close();
    });
    NetInfo->m_context.close();
    zmq::socket_t _socket;
    
    return true;
}
bool NetMsgRecv(const int64_t& dt_, entt::registry& reg_) {
    reg_.view<SocketCpt>().each([&dt_](auto& socket_) {
        //如果作为 route 收到的消息,这个时候消息结构为   route_id protobuf_name protobuf_val
        //如果作为 dealer 收到的消息,这个时候消息结构为  protobuf_name protobuf_val
        //差异为 2个消息或3个消息
        std::vector<std::string> _recv;
        while (true) {
            static zmq::message_t _tmp_msg;
            if (socket_.socket->recv(_tmp_msg, zmq::recv_flags::dontwait)) {
                _recv.push_back(_tmp_msg.to_string());
                if (!_tmp_msg.more()) {
                    break;
                }
            }
            else {
                break;
            }
        }

        if (_recv.size() == 3) {
            std::shared_ptr<Message> _msg(ProtoCodec->decode(_recv[1], _recv[2]));
            if (_msg.get()) {
                DispatcherEvent(socket_.socket, _msg, dt_, _recv[0]);
            }

        }
        else if (_recv.size() == 2) {
            std::shared_ptr<Message> _msg(ProtoCodec->decode(_recv[0], _recv[1]));
            if (_msg.get()) {
                DispatcherEvent(socket_.socket, _msg, dt_, _recv[0]);
            }
        }

    });
    return true;
}

bool NetMsgSend(const int64_t& dt_, entt::registry& reg_) {
    auto _view = reg_.view<RouteIDCpt, SocketCpt, ConnectCpt, SendSocket>();
    for(auto _entity_it : _view) {
        auto& _msg_list = _view.get<ConnectCpt>(_entity_it);
        auto& _route_id = _view.get<RouteIDCpt>(_entity_it);
        auto& _socket = _view.get<SocketCpt>(_entity_it);
        for (auto& _msg_it : _msg_list.msg_list) {
            if (_route_id.route_id != "") {
                zmq::send_result_t _route_id_result = _socket.socket->send(zmq::buffer(_route_id.route_id), zmq::send_flags::sndmore);
                if (_route_id_result == -1) {
                    zmq::error_t _err;
                    LogInfo << "send error: " << _err.what() << FlushLog;
                }
            }
            static std::string _buff;
            _buff.clear();
            if (_msg_it->SerializeToString(&_buff)) {
                zmq::send_result_t _result = _socket.socket->send(zmq::buffer(_msg_it->GetTypeName()), zmq::send_flags::sndmore);
                if (_result == -1) {
                    zmq::error_t _err;
                    LogInfo << "send error: " << _err.what() << FlushLog;
                }
                zmq::send_result_t _more_result = _socket.socket->send(zmq::buffer(_buff), zmq::send_flags::none);
                if (_more_result == -1) {
                    zmq::error_t _err;
                    LogInfo << "send error: " << _err.what() << FlushLog;
                }
            }
        }
        _msg_list.msg_list.clear();
    }
    //reg_.view<RouteIDCpt,SocketCpt, ConnectCpt, OtherSocket>().each([](auto& route_id_,auto& socket_, auto& msg_list_, auto& other_socket_) {
    //    for (auto& _msg_it : msg_list_.msg_list) {
    //        if (route_id_.route_id != "") {
    //            zmq::send_result_t _route_id_result = socket_.socket->send(zmq::buffer(route_id_.route_id), zmq::send_flags::sndmore);
    //            if (_route_id_result == -1) {
    //                zmq::error_t _err;
    //                LogInfo << "send error: " << _err.what() << FlushLog;
    //            }
    //        }
    //        static std::string _buff;
    //        _buff.clear();
    //        if (_msg_it->SerializeToString(&_buff)) {
    //            zmq::send_result_t _result = socket_.socket->send(zmq::buffer(_msg_it->GetTypeName()), zmq::send_flags::sndmore);
    //            if (_result == -1) {
    //                zmq::error_t _err;
    //                LogInfo << "send error: " << _err.what() << FlushLog;
    //            }
    //            zmq::send_result_t _more_result = socket_.socket->send(zmq::buffer(_buff), zmq::send_flags::none);
    //            if (_more_result == -1) {
    //                zmq::error_t _err;
    //                LogInfo << "send error: " << _err.what() << FlushLog;
    //            }
    //        }
    //    }
    //    msg_list_.msg_list.clear();
    //});



    return true;
}

MgrRegHelper(NetMgr) {
    SYSMGR->regInitSys(NetInit);
    SYSMGR->regDestorySys(NetDestory);
    SYSMGR->regSys(SystemLevel::MSGRECV, NetMsgRecv);
    SYSMGR->regSys(SystemLevel::MSGSEND, NetMsgSend);
}

