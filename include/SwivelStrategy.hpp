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

public:
    SwivelStrategy();
    geometry_msgs::Twist step(BumperData bumperData, LaserData laserData, OdomData odomData) override;
    bool IsFinished = false;
};

#endif