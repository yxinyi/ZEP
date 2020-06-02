#include "SystemManager.h"


SystemManager::SystemManager():m_system_pool(static_cast<size_t>(SystemLevel::MAX)) {

}


void SystemManager::regSys(const SystemLevel& system_level_, SystemFunc&& func_) {
    m_system_pool[static_cast<size_t>(system_level_)].push_back(std::forward<SystemFunc>(func_));
}

void SystemManager::loop(const int64_t& time_, entt::registry& registry_) {
    for (const auto& _lev_pool_it : m_system_pool) {
        for (const auto& _sys_it : _lev_pool_it) {
            _sys_it(time_,registry_);
        }
    }
}

void SystemManager::regInitSys(SystemInitFunc&& func_) {
    m_init_pool.push_back(std::forward<SystemInitFunc>(func_));
}

void SystemManager::init(entt::registry& registry_) {
    for (const auto& _sys_it : m_init_pool) {
        _sys_it(registry_);
    }
}