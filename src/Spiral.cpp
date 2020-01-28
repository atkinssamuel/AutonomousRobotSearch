#include <chrono>
#include <ros/console.h>
#include "ros/ros.h"
#include <kobuki_msgs/BumperEvent.h>
#include "Spiral.hpp"

Spiral::Spiral()
{
    _moving = true;
}

geometry_msgs::Twist Spiral::step(uint8_t bumper[3], float minLaserDistance)
{
    geometry_msgs::Twist vel;

    if (_moving) {

        if (minLaserDistance > 0.5 && minLaserDistance < 100) {
            _moving = true;

            vel.linear.x = 0.5;
            vel.angular.z = 1;
        }
        else {
            _moving = false;
            vel.linear.x = 0;
            vel.angular.z = 0;
        }
    }
    else {

        vel.linear.x = 0;
        vel.angular.z = 1;
        if (minLaserDistance > .5 && minLaserDistance < 100) {
            _moving = true;

            vel.linear.x = 0.5;
            vel.angular.z = 1;
        }
    }

    return vel;
};
