#include <functional>
#include "include/entt.hpp"
#include "systems/SystemManager.h"
#include "include/tool/ManagerInitHelper.h"
#include "include/tool/SingletonTemplate.h"
#include "include/tool/LogInfo.h"


class BallTag final
{
public:
    BallTag() = default;
    ~BallTag() = default;
    BallTag& operator=(const BallTag&) noexcept;
};