#ifndef DEMOSTRATEGY_H
#define DEMOSTRATEGY_H

#include <chrono>
#include <geometry_msgs/Twist.h>
#include "IStrategy.hpp"

class DemoStrategy : public IStrategy
{
private:
    bool _movingForward;
    bool _turning;

public:
    DemoStrategy();

    geometry_msgs::Twist step(BumperData bumperData, LaserData laserData, OdomData odomData) override;
};

#endif