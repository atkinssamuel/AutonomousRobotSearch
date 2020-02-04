#ifndef MOVEFORWARDSTRATEGY_H
#define MOVEFORWARDSTRATEGY_H

#include <geometry_msgs/Twist.h>
#include "IStrategy.hpp"

class MoveForwardStrategy : public IStrategy
{
public:
    geometry_msgs::Twist step(BumperData bumperData, LaserData laserData, OdomData odomData, uint64_t secondsElapsed) override;
};

#endif