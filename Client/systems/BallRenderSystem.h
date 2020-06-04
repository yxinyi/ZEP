#include <functional>
#include "include/entt.hpp"
#include "include/tool/ManagerInitHelper.h"
#include "include/tool/SingletonTemplate.h"
#include "systems/RenderManager.h"

#include "../../Common/include/tool/LogInfo.h"

extern bool BallRender(SDL_Renderer* render_, SDL_Window* window_, entt::registry& reg_);
