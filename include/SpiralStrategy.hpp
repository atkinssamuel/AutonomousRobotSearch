#ifndef SPIRALSTRATEGY_H
#define SPIRALSTRATEGY_H

#include <chrono>
#include <geometry_msgs/Twist.h>
#include "IStrategy.hpp"

class SpiralStrategy : public IStrategy
{
private:
    bool _moving;

public:
    SpiralStrategy();

    geometry_msgs::Twist step(BumperData bumperData, LaserData laserData, OdomData odomData) override;
};

#endif
