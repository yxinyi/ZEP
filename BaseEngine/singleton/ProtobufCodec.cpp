#include "ProtobufCodec.h"
using namespace google::protobuf;
#include "include/tool/LogInfo.h"
#include "./include/proto/Ball.pb.h"


Message* ProtobufCodec::createMessage(const std::string& proto_name_) {
    Message* _msg = nullptr;
    if (const Descriptor* _descripotr = DescriptorPool::generated_pool()->FindMessageTypeByName(proto_name_.data())) {
        if (const Message* _prototype = MessageFactory::generated_factory()->GetPrototype(_descripotr)) {
            _msg = _prototype->New();
        }
    }
    return _msg;
}
Message* ProtobufCodec::decode(const std::string& proto_name_, const std::string& zmq_msg_) {
    Message* _msg = nullptr;
    if (_msg = createMessage(proto_name_)) {
        _msg->ParseFromString(zmq_msg_);
    }
    return _msg;
}
