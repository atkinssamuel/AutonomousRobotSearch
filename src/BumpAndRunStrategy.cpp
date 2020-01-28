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

geometry_msgs::Twist BumpAndRunStrategy::step(BumperData bumperData, LaserData LaserData)
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

        if (bumperData.anyBumperPressed())
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