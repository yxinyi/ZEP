#pragma once
#include <functional>
#include "include/tool/SingletonTemplate.h"
#include "include/entt.hpp"

using SystemFunc = std::function<bool(const int64_t&, entt::registry&)>;
using SystemInitFunc = std::function<bool(entt::registry&)>;
using SystemDestoryFunc = std::function<bool(entt::registry&)>;
enum class SystemLevel
{
    BEFORE = 0,
    NORMAl = 1,
    AFTER = 2,
    MAX = 2,
};

class SystemManager {
    friend class Singleton<SystemManager>;
public:
    void regInitSys(SystemInitFunc&& func_) {
        m_init_pool.push_back(std::forward<SystemInitFunc>(func_));
    }

    void regDestorySys(SystemDestoryFunc&& func_) {
        m_destory_pool.push_back(std::forward<SystemDestoryFunc>(func_));
    }
    void regSys(const SystemLevel& system_level_, SystemFunc&& func_) {
        m_system_pool[static_cast<size_t>(system_level_)].push_back(std::forward<SystemFunc>(func_));
    }
    void init(entt::registry& registry_) {
        for (const auto& _sys_it : m_init_pool) {
            _sys_it(registry_);
        }
    }
    void destory(entt::registry& registry_) {
        for (const auto& _sys_it : m_destory_pool) {
            _sys_it(registry_);
        }
    }
    void loop(const int64_t& time_, entt::registry& registry_) {
        for (const auto& _lev_pool_it : m_system_pool) {
            for (const auto& _sys_it : _lev_pool_it) {
                _sys_it(time_, registry_);
            }
        }
    }
    ~SystemManager() {
    };

private:
    SystemManager() :m_system_pool(static_cast<size_t>(SystemLevel::MAX)) {}
    std::vector<std::vector<SystemFunc>> m_system_pool; //system lev func vec
    std::vector<SystemInitFunc> m_init_pool;
    std::vector<SystemDestoryFunc> m_destory_pool;
};

#define SYSMGR Singleton<SystemManager>::getInstance()