#include <functional>
#include "include/entt.hpp"
#include "systems/SystemManager.h"
#include "include/tool/ManagerInitHelper.h"
#include "include/tool/SingletonTemplate.h"
#include "include/tool/LogInfo.h"


extern bool MoveMgrUpdate(const int64_t&, entt::registry&);
extern bool MoveMgrInit(entt::registry&);
