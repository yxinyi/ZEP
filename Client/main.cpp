#include <cstdint>
#include <stdio.h>
#include "include/entt.hpp"
#include "include/tool/LogInfo.h"
#include "include/zmq/cppzmq/zmq_addon.hpp"
#include "../BaseEngine/systems/SystemManager.h"
#include <windows.h>
#include <iostream>
#include "./include/proto/Ball.pb.h"
#include "include/tool/Timer.h"

//struct position {
//    float x;
//    float y;
//};
//
//struct velocity {
//    float dx;
//    float dy;
//};
//
//void update(entt::registry& registry) {
//    auto view = registry.view<position, velocity>();
//
//    for (auto entity : view) {
//        // gets only the components that are going to be used ...
//
//        auto& vel = view.get<velocity>(entity);
//
//        vel.dx = 0.;
//        vel.dy = 0.;
//        
//        // ...
//    }
//}
//
//void update(std::uint64_t dt, entt::registry& registry) {
//    registry.view<position, velocity>().each([dt](auto& pos, auto& vel) {
//        // gets all the components of the view at once ...
//
//        pos.x += vel.dx * dt;
//        pos.y += vel.dy * dt;
//        // ...
//    });
//}




int main() {
    //entt::registry registry;
    //std::uint64_t dt = 16;
    //
    //zmq::context_t context;
    //zmq::socket_t sock(context, zmq::socket_type::dealer);
    //sock.connect("tcp://127.0.0.1:7000");
    ////zmq::message_t msg("asd");
    //uint32_t _time = time(0);
    //uint32_t _cnt = 0;
    //for (;;) {
    //    zmq::message_t _msg(std::to_string(_time));
    //    sock.send(_msg, zmq::send_flags::sndmore);        
    //    sock.send(zmq::buffer(std::to_string(_cnt++)), zmq::send_flags::dontwait);
    //    Sleep(10);
    //    if (sock.recv(_msg, zmq::recv_flags::dontwait)) {
    //        std::cout << _msg.str() << std::endl;
    //    }
    //}
    
    //for (auto i = 0; i < 1000000000; ++i) {
    //    auto entity = registry.create();
    //    registry.emplace<position>(entity, i * 1.f, i * 1.f);
    //    if (i % 2 == 0) { registry.emplace<velocity>(entity, i * .1f, i * .1f); }
    //}
    //uint64_t _cnt = 0;
    //for (;;) {
    //    update(dt, registry);
    //    update(registry);
    //    printf("%llu \n", ++_cnt);
    //}


    //try
    //{
    //    while()
    //    double time = 0;
    //    double accumulator = 0.0;
    //
    //    // 60 updates per second. We divide 1000 by 60 instead of 1 because sdl operates on milliseconds 
    //    // not nanoseconds.
    //    const double deltaTime = 1000.0 / 60.0;
    //
    //    const double newTime = SDL_GetTicks();
    //    const double frameTime = newTime - currentTime;
    //    currentTime = newTime;
    //
    //    accumulator += frameTime;
    //
    //    while (accumulator >= deltaTime) {
    //        SystemManager::getInstance()->loop();
    //        accumulator -= deltaTime;
    //        time += deltaTime;
    //    }
    //}
    //catch (const std::exception& e)
    //{
    //    LogError << "Exception: " << e.what() << FlushLog;
    //}
    //catch (...)
    //{
    //    LogError << "Threw an unknown exception. Please derive from std::exception." << FlushLog;
    //}


    zmq::context_t context;
    zmq::socket_t sock(context, zmq::socket_type::sub);
    sock.connect("tcp://127.0.0.1:7000");
    sock.set(zmq::sockopt::subscribe, "");
    zmq::message_t msg;
    Timer _tick_timer;
    while (1) {
        if (sock.recv(msg, zmq::recv_flags::dontwait)) {
            _tick_timer.reset();
            BallUpdateEvent _update_event;
            _update_event.ParseFromString(msg.to_string());
            uint32_t _size = _update_event.size();
            LogInfo << "size: " << _size << FlushLog;
            for (uint32_t _idx = 0; _idx < _size; _idx++) {
                const Ball& _ball = _update_event.ball(_idx);
                //LogInfo << "oid: " << _ball.oid() << " x: " << _ball.x() << " y: " << _ball.y() << FlushLog;
            }
            LogError << "frame tick :  " << _tick_timer.elapsed()  << FlushLog;
        }
    }
    return 0;
}