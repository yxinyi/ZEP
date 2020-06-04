#include <functional>
#include "include/entt.hpp"
#include "systems/SystemManager.h"
#include "singleton/GameWindow.h"
#include "include/tool/ManagerInitHelper.h"
#include "include/tool/SingletonTemplate.h"
#include "../../Common/include/tool/LogInfo.h"
#include "SDL2/SDL.h"


extern bool WindowUpdate(const int64_t&, entt::registry&);
extern bool WindowInit(entt::registry&);
