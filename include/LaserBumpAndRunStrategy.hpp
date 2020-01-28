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

    geometry_msgs::Twist step(uint8_t bumper[3], float minLaserDistance) override;
};

#endif