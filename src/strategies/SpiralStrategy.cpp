#include <chrono>
#include <ros/console.h>
#include "ros/ros.h"
#include <kobuki_msgs/BumperEvent.h>
#include "SpiralStrategy.hpp"

SpiralStrategy::SpiralStrategy()
{
    _moving = true;
}

geometry_msgs::Twist SpiralStrategy::step(BumperData bumperData, LaserData laserData, OdomData OdomData)
{
    geometry_msgs::Twist vel;

    if (_moving)
    {
        if (laserData.getMinDistance() > 0.5 && laserData.getMinDistance() < 100)
        {
            _moving = true;

            vel.linear.x = 0.5;
            vel.angular.z = 1;
        }
        else
        {
            _moving = false;
            vel.linear.x = 0;
            vel.angular.z = 0;
        }
    }
    else
    {
        vel.linear.x = 0;
        vel.angular.z = 1;
        if (laserData.getMinDistance() > .5 && laserData.getMinDistance() < 100)
        {
            _moving = true;

            vel.linear.x = 0.5;
            vel.angular.z = 1;
        }
    }

    return vel;
};
