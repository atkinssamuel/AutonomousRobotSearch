#include <chrono>
#include <kobuki_msgs/BumperEvent.h>
#include "BumpAndRunStrategy.hpp"

#define N_BUMPER (3)

BumpAndRunStrategy::BumpAndRunStrategy()
{
    _turning = false;
    _movingForward = true;

    _turnTimeThreshold = 10; //seconds
}

geometry_msgs::Twist BumpAndRunStrategy::step(uint8_t bumper[3], float minLaserDistance)
{
    geometry_msgs::Twist vel;

    if (_turning)
    {
        vel.linear.x = 0.0;
        vel.angular.z = 0.3;

        std::chrono::time_point<std::chrono::system_clock> currTime = std::chrono::system_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(currTime - _turnStartTime).count() > _turnTimeThreshold)
        {
            vel.linear.x = 0.0;
            vel.angular.z = 0.0;

            _movingForward = true;
            _turning = false;
        }
    }
    else if (_movingForward)
    {
        vel.linear.x = 0.1;
        vel.angular.z = 0.0;

        bool any_bumper_pressed = false;
        for (uint32_t b_idx = 0; b_idx < N_BUMPER; ++b_idx)
        {
            any_bumper_pressed |= (bumper[b_idx] == kobuki_msgs::BumperEvent::PRESSED);
        }

        if (any_bumper_pressed)
        {
            vel.linear.x = 0.0;
            vel.angular.z = 0.0;

            _turnStartTime = std::chrono::system_clock::now();

            _movingForward = false;
            _turning = true;
        }
    }

    return vel;
};