#ifndef SWIVELSTRATEGY_H
#define SWIVELSTRATEGY_H

#include <chrono>
#include <geometry_msgs/Twist.h>
#include "IStrategy.hpp"

class SwivelStrategy : public IStrategy
{
private:
    geometry_msgs::Twist vel;

    bool _init;
    bool _left;
    bool _right;
    bool _straighten;

    double _leftAngle;
    double _rightAngle;
    double _straightenAngle;
    double _angleThreshold;
    bool IsFinished;
    
    std::chrono::time_point<std::chrono::system_clock> _startTime;
    uint64_t _timeElapsed;


public:
    SwivelStrategy();
    geometry_msgs::Twist step(BumperData bumperData, LaserData laserData, OdomData odomData) override;
    bool getIsFinished();
};

#endif
