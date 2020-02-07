#include <chrono>
#include <kobuki_msgs/BumperEvent.h>
#include "DemoStrategy.hpp"

DemoStrategy::DemoStrategy()
{
    _turning = false;
    _movingForward = true;
}

geometry_msgs::Twist DemoStrategy::step(BumperData bumperData, LaserData laserData, OdomData odomData)
{
    geometry_msgs::Twist vel;

    float minLaserDistance = laserData.getMinDistance();

    if (_turning)
    {
        vel.linear.x = 0.0;
        vel.angular.z = 0.3;

        if (minLaserDistance > 1 && minLaserDistance < 100)
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

        if (minLaserDistance < 0.5 || minLaserDistance > 100)
        {
            vel.linear.x = 0.0;
            vel.angular.z = 0.0;

            _movingForward = false;
            _turning = true;
        }
    }

    return vel;
};