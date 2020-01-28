#ifndef ISTRATEGY_H
#define ISTRATEGY_H

#include <geometry_msgs/Twist.h>

#include "BumperData.hpp"
#include "LaserData.hpp"
#include "OdomData.hpp"

class IStrategy
{
public:
    virtual geometry_msgs::Twist step(BumperData bumperData, LaserData laserData, OdomData odomData) = 0;
};

#endif
