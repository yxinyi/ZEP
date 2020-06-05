#include <memory>
#include "BallRenderSystem.h"
#include "components/PositionComponent.h"
#include "components/VectorComponent.h"
#include "components/ObjectidComponent.h"
#include "entitys/BallEntity.h"

#include<random>  
#include<time.h> 

std::vector<int> _x_vec(20000);
std::vector<int> _y_vec(20000);
std::default_random_engine _random(time(NULL));
std::uniform_real_distribution<float> _random_x_range(0.f, 1280.0);
std::uniform_real_distribution<float> _random_y_range(0.f, 720.0);
std::uniform_real_distribution<float> _random_speed_x_range(-10.f, 10.f);
std::uniform_real_distribution<float> _random_speed_y_range(-10.f, 10.f);
bool BallRender(SDL_Renderer* render_, SDL_Window* window_, entt::registry& reg_) {

    reg_.view<BallTag, PositionComponent>().each([&render_](auto& tag_,auto& pos_) {
        SDL_SetRenderDrawColor(render_, 255, 0, 0, 255);
        SDL_Rect rectToDraw{pos_.x, pos_.y, 1, 1 };
        SDL_RenderFillRect(render_, &rectToDraw);
    });

    return true;
}

MgrRegHelper(BallRender) {
    RenderMgr->regRenderFunc(BallRender);
}
