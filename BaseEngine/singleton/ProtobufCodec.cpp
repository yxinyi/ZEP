#include "./ProtobufCodec.h"
using namespace google::protobuf;


Message* ProtobufCodec::createMessage(std::string_view proto_name_) {
    Message* _msg = nullptr;
    if (const Descriptor* _descripotr = DescriptorPool::generated_pool()->FindMessageTypeByName(proto_name_.data())) {
        if (const Message* _prototype = MessageFactory::generated_factory()->GetPrototype(_descripotr)) {
            _msg = _prototype->New();
        }
    }
    return _msg;
}
Message* ProtobufCodec::decode(std::string_view proto_name_, std::string_view zmq_msg_) {
    Message* _msg = nullptr;
    if (_msg = createMessage(proto_name_)) {
        _msg->ParseFromString(zmq_msg_.data());
    }
    return _msg;
}
