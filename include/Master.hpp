#ifndef MASTER_H
#define MASTER_H

#include <chrono>
#include <geometry_msgs/Twist.h>
#include "IStrategy.hpp"

class Master : public IStrategy
{
private:
    geometry_msgs::Twist vel;
    IStrategy *strategy;
    
    bool _newSpinStrategy;

    bool _spinStrategy;



public:
    Master();
    geometry_msgs::Twist step(BumperData bumperData, LaserData laserData, OdomData odomData, uint64_t secondsElapsed) override;
};

#endif