
#include "MoveForwardStrategy.hpp"

geometry_msgs::Twist MoveForwardStrategy::step(BumperData bumperData, LaserData laserData, OdomData odomData, uint64_t secondsElapsed)
{
    geometry_msgs::Twist vel;

    vel.linear.x = 0.2;
    vel.angular.z = 0;

    return vel;
};