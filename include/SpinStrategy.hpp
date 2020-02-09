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
    geometry_msgs::Twist vel;
    float _finalAngle;

    std::chrono::time_point<std::chrono::system_clock> _startTime;

    double _angleThreshold;
    double _secondsElapsed;
    double _holdoutTime;
    bool _finished;

public:
    SpinStrategy();
    bool getIsFinished() override;
    geometry_msgs::Twist step(BumperData bumperData, LaserData laserData, OdomData odomData) override;
};

#endif