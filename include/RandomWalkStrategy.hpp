#ifndef RANDOMWALK_H
#define RANDOMWALK_H

#include <chrono>
#include <geometry_msgs/Twist.h>
#include "IStrategy.hpp"

class RandomWalk : public IStrategy
{
private:
    uint64_t _turnTimeThreshold;       //seconds
    uint64_t _randomTurnTimeThreshold; //seconds
    std::chrono::time_point<std::chrono::system_clock> _turnStartTime;
    std::chrono::time_point<std::chrono::system_clock> _randomTurnStartTime;

    bool _movingForward;
    bool _turning;
    bool _turningRandom;

    float angular;
    float linear;

public:
    RandomWalk();

    geometry_msgs::Twist step(BumperData bumperData, LaserData laserData, OdomData odomData) override;
};

#endif
