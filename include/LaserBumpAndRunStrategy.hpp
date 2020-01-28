#ifndef LASERBUMPANDRUNSTRATEGY_H
#define LASERBUMPANDRUNSTRATEGY_H

#include <chrono>
#include <geometry_msgs/Twist.h>
#include "IStrategy.hpp"

class LaserBumpAndRunStrategy : public IStrategy
{
private:
    bool _movingForward;
    bool _turning;

public:
    LaserBumpAndRunStrategy();

    geometry_msgs::Twist step(BumperData bumperData, LaserData laserData) override;
};

#endif