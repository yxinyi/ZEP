#pragma once
#include<chrono>
#include "include/tool/LogInfo.h"


class Timer
{
public:
    Timer() : m_begin(std::chrono::high_resolution_clock::now()) {}

    void reset()
    {
        m_begin = std::chrono::high_resolution_clock::now();
    }

    //ƒ¨»œ ‰≥ˆ∫¡√Î
    int64_t elapsed() const
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - m_begin).count();
    }

    //Œ¢√Î
    int64_t elapsed_micro() const
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now() - m_begin).count();
    }

    //ƒ…√Î
    int64_t elapsed_nano() const
    {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now() - m_begin).count();
    }

    //√Î
    int64_t elapsed_seconds() const
    {
        return std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::high_resolution_clock::now() - m_begin).count();
    }

    //∑÷
    int64_t elapsed_minutes() const
    {
        return std::chrono::duration_cast<std::chrono::minutes>(
            std::chrono::high_resolution_clock::now() - m_begin).count();
    }

    // ±
    int64_t elapsed_hours() const
    {
        return std::chrono::duration_cast<std::chrono::hours>(
            std::chrono::high_resolution_clock::now() - m_begin).count();
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_begin;
};


class PerFormanceProbe {
public:
    PerFormanceProbe(std::string probe_name_) {
        m_probe_name = probe_name_;
    }
    ~PerFormanceProbe() {
        LogInfo << m_probe_name << " : " << m_timer.elapsed_micro() << "millis sceonds" << FlushLog; \
    }
private:
    std::string m_probe_name;
    Timer m_timer;
};
