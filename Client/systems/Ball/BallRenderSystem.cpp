#include <memory>
#include "BallRenderSystem.h"
#include "components/PositionComponent.h"
#include "components/VectorComponent.h"
#include "components/ObjectidComponent.h"
#include "entitys/BallEntity.h"
#include "include/tool/Timer.h"

#include<random>  
#include<time.h> 

bool BallRender(SDL_Renderer* render_, SDL_Window* window_, entt::registry& reg_) {
    reg_.view<BallTag, PositionComponent>().each([&render_](auto& tag_,auto& pos_) {
        SDL_SetRenderDrawColor(render_, 255, 0, 0, 255);
        SDL_FRect rectToDraw{pos_.x, pos_.y, 1, 1};
        SDL_RenderFillRectF(render_, &rectToDraw);
    });
    return true;
}

MgrRegHelper(BallRender) {
    RenderMgr->regRenderFunc(BallRender);
}
