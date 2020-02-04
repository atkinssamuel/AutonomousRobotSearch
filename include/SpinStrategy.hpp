#ifndef SPINSTRATEGY_H
#define SPINSTRATEGY_H

#include <chrono>
#include <geometry_msgs/Twist.h>
#include "IStrategy.hpp"

class SpinStrategy : public IStrategy
{
private:
    bool _init;
    bool _spin;

public:
    SpinStrategy();
    bool _finished;
    geometry_msgs::Twist step(BumperData bumperData, LaserData laserData, OdomData odomData) override;
};

#endif