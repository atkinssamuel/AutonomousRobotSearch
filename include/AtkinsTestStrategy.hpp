#ifndef ATKINSTESTSTRATEGY_H
#define ATKINSTESTSTRATEGY_H

#include <chrono>
#include <geometry_msgs/Twist.h>
#include "IStrategy.hpp"

class AtkinsTestStrategy : public IStrategy
{
private:
    bool _movingForward;
    bool _turning;

public:
    AtkinsTestStrategy();

    geometry_msgs::Twist step(BumperData bumperData, LaserData laserData, OdomData odomData, uint64_t secondsElapsed) override;
};

#endif