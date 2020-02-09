#ifndef RANDOMWALKSTRATEGY_H
#define RANDOMWALKSTRATEGY_H

#include <chrono>
#include <geometry_msgs/Twist.h>
#include "IStrategy.hpp"

class RandomWalkStrategy : public IStrategy
{
private:
    uint64_t _turnTimeThreshold;       //seconds
    float _randomTurnTimeThreshold; //seconds
    std::chrono::time_point<std::chrono::system_clock> _turnStartTime;
    std::chrono::time_point<std::chrono::system_clock> _randomTurnStartTime;

    bool _movingForward;
    bool _turning;
    bool _turningRandom;

    float angular;
    float linear;
    bool IsFinished;
    
public:
    RandomWalkStrategy();
    geometry_msgs::Twist step(BumperData bumperData, LaserData laserData, OdomData odomData) override;
    bool getIsFinished() override;
};

#endif
