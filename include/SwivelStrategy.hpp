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
    bool IsFinished;

    double _turnVelocity;
    
    std::chrono::time_point<std::chrono::system_clock> _startTime;
    std::chrono::time_point<std::chrono::system_clock> _turnTime;

    uint64_t _shortTurnThreshold;
    uint64_t _longTurnThreshold;
    uint64_t _turnTimeElapsed;
    uint64_t _timeElapsed;
    uint64_t _failureTime;


public:
    SwivelStrategy();
    geometry_msgs::Twist step(BumperData bumperData, LaserData laserData, OdomData odomData) override;
    bool getIsFinished();
};

#endif
