#include "UniqueNumberFactory.h"
#include "../Common/include/tool/Time.h"

//temp logic
uint64_t UniqueNumberFactory::build() {
    uint64_t _this_timestamp = static_cast<uint64_t>(Time::getInstance()->Now());
    static uint64_t _the_slot = 0;
    if (_the_slot == 0xFFFFFFFF) {
        _the_slot = 0;
    }

    return _this_timestamp << 32 | _the_slot++;
}

UniqueNumberFactory::UniqueNumberFactory() {}
uint64_t APIGetUniqueNumber() {
    return UniqueNumberFactory::getInstance()->build();
}

