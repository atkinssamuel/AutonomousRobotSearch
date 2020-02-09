#ifndef DEMOSTRATEGY_H
#define DEMOSTRATEGY_H

#include <chrono>
#include <geometry_msgs/Twist.h>
#include "IStrategy.hpp"

class DemoStrategy : public IStrategy
{
private:
    bool _newSwivelStrategy;
    bool _swivelStrategy;
    bool IsFinished;
    IStrategy *strategy;


public:
    DemoStrategy();
    bool getIsFinished() override;
    geometry_msgs::Twist step(BumperData bumperData, LaserData laserData, OdomData odomData) override;
};

#endif