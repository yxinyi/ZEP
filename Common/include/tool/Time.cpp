#include "Time.h"
#include <ctime>
#include <iomanip>
#include <sstream>

int64_t Time::Now() {
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

int64_t Time::NowMillisecond() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
std::string Time::NowStr() {
    auto _time_point = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    //×ªÎª×Ö·û´®
    std::stringstream _tmp_str;
    tm _tm;
    localtime_s(&_tm, &_time_point);
    _tmp_str << std::put_time(&_tm, "%Y-%m-%d-%H-%M-%S");
    return _tmp_str.str();
}