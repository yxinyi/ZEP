#pragma once
#include <functional>
#include "include/tool/SingletonTemplate.h"
#include "include/entt.hpp"

using SystemFunc = std::function<bool(const int64_t&, entt::registry&)>;
using SystemInitFunc = std::function<bool(entt::registry&)>;
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
    void regInitSys(SystemInitFunc&& func_);
    void regSys(const SystemLevel& system_level_, SystemFunc&& func_);
    void init(entt::registry& registry_);
    void loop(const int64_t& time_, entt::registry& registry_);
    ~SystemManager()=default;

private:
    SystemManager();
    std::vector<std::vector<SystemFunc>> m_system_pool; //system lev func vec
    std::vector<SystemInitFunc> m_init_pool; 
};

#define SYSMGR Singleton<SystemManager>::getInstance()