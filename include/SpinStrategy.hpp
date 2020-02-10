#ifndef SPINSTRATEGY_H
#define SPINSTRATEGY_H

#include <chrono>
#include <geometry_msgs/Twist.h>
#include "IStrategy.hpp"

class SpinStrategy : public IStrategy
{
private:
    bool _spin;
    geometry_msgs::Twist vel;

    std::chrono::time_point<std::chrono::system_clock> _startTime;

    float _timeElapsed;
    float _turnTime;

    double _turningVelocity;
    bool IsFinished;

public:
    SpinStrategy();
    bool getIsFinished() override;
    geometry_msgs::Twist step(BumperData bumperData, LaserData laserData, OdomData odomData) override;
};

#endif