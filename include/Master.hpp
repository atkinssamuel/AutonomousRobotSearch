#ifndef MASTER_H
#define MASTER_H

#include <chrono>
#include <geometry_msgs/Twist.h>
#include "IStrategy.hpp"

class Master : public IStrategy
{
private:
    geometry_msgs::Twist vel;
    uint64_t _secondsElapsed;
    std::chrono::time_point<std::chrono::system_clock> _startTime;

    IStrategy *strategy;
    
    bool _newSpinStrategy;
    bool _newSwivelStrategy;

    bool _spinStrategy;
    bool _swivelStrategy;



public:
    Master();
    geometry_msgs::Twist step(BumperData bumperData, LaserData laserData, OdomData odomData) override;
};

#endif