#include <memory>
#include "components/PositionComponent.h"
#include "components/VectorComponent.h"
#include "components/ObjectidComponent.h"
#include "entitys/BallEntity.h"
#include "../../Common/include/zmq/cppzmq/zmq_addon.hpp"
#include "singleton/EnvironmentInfo.h"
#include "../Server/singleton/SendBuffDispatch.h"
#include "./include/proto/Ball.pb.h"
#include "../Server/singleton/NerConnect.h"


extern bool ProtoBuildUpdate(const int64_t&, entt::registry&);
extern bool ProtoBuildInit(entt::registry&);

bool ProtoBuildInit(entt::registry& reg_) {
    LogInfo << "ProtoBuildInit" << FlushLog;
    return true;
}
bool ProtoBuildUpdate(const int64_t& dt_, entt::registry& reg_) {

    //�����������,�Ƚ���ȫͬ��
    if (reg_.view<NewConnect>().size()) {
        std::shared_ptr<BallUpdateEvent> _all_update_event(new BallUpdateEvent());
        auto _view = reg_.view<BallTag, VectorComponent, PositionComponent, ObjectidComponent>();
        _all_update_event->set_size(_view.size());
        for (auto _entity_it : _view) {
            Ball* _ball = _all_update_event->add_ball();
            _ball->set_oid(_view.get<ObjectidComponent>(_entity_it).oid);
            auto _pos = _view.get<PositionComponent>(_entity_it);
            _ball->set_x(_pos.x);
            _ball->set_y(_pos.y);
            auto _vector = _view.get<VectorComponent>(_entity_it);
            _ball->set_vector_x(_vector.x);
            _ball->set_vector_y(_vector.y);
        }

        //�����������ӽ�����Ϣ����
        auto _new_connect_view = reg_.view<NewConnect, Connect>();
        for (auto& _new_connect_it : _new_connect_view) {
            LogInfo << "new connect all update" << FlushLog;
            auto& _connect_msg = _new_connect_view.get<Connect>(_new_connect_it);
            _connect_msg.m_msg_list.push_back(_all_update_event);
            reg_.remove_if_exists<NewConnect>(_new_connect_it);
        }
    }
    
    //����������仯����У��
    if (reg_.view<VectorChange>().size()) {
        std::shared_ptr<BallUpdateEvent> _update_event(new BallUpdateEvent());
        auto _view = reg_.view<BallTag, VectorChange, VectorComponent, PositionComponent, ObjectidComponent>();
        _update_event->set_size(_view.size());
        for (auto _entity_it : _view) {
            Ball* _ball = _update_event->add_ball();
            _ball->set_oid(_view.get<ObjectidComponent>(_entity_it).oid);
            auto _pos = _view.get<PositionComponent>(_entity_it);
            _ball->set_x(_pos.x);
            _ball->set_y(_pos.y);
            auto _vector = _view.get<VectorComponent>(_entity_it);
            _ball->set_vector_x(_vector.x);
            _ball->set_vector_y(_vector.y);
            reg_.remove_if_exists<VectorChange>(_entity_it);
        }
        //���������ӽ��д���
        reg_.view<Connect>().each([&_update_event,&_view](auto& connect) {
            connect.m_msg_list.push_back(_update_event);
        });
        //LogInfo << "connect diff update" << _view.size() << FlushLog;
    }
    return true;
}

MgrRegHelper(ProtoBuild) {
    SYSMGR->regInitSys(ProtoBuildInit);
    SYSMGR->regSys(SystemLevel::NORMAl, ProtoBuildUpdate);
}
