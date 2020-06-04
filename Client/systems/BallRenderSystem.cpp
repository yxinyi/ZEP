#include <memory>
#include "BallRenderSystem.h"
#include "components/PositionComponent.h"
#include "components/VectorComponent.h"
#include "components/ObjectidComponent.h"
#include "entitys/BallEntity.h"


bool BallRender(SDL_Renderer* render_, SDL_Window* window_, entt::registry& reg_) {
    reg_.view<BallTag, PositionComponent>().each([&render_](auto& tag_,auto& pos_) {
        SDL_SetRenderDrawColor(render_, 255, 0, 0, 255);
        SDL_Rect rectToDraw{pos_.x, pos_.y, 10, 10 };
        SDL_RenderFillRect(render_, &rectToDraw);
    });
    LogInfo << reg_.view<BallTag, PositionComponent>().size() << FlushLog;
    return true;
}

MgrRegHelper(BallRender) {
    RenderMgr->regRenderFunc(BallRender);
}
