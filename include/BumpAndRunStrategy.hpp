#ifndef BUMPANDRUNSTRATEGY_H
#define BUMPANDRUNSTRATEGY_H

#include <chrono>
#include <geometry_msgs/Twist.h>
#include "IStrategy.hpp"

class BumpAndRunStrategy : public IStrategy
{
private:
    uint64_t _turnTimeThreshold; //seconds
    std::chrono::time_point<std::chrono::system_clock> _turnStartTime;

    bool _movingForward;
    bool _turning;

public:
    BumpAndRunStrategy();

    geometry_msgs::Twist step(uint8_t bumper[3], float minLaserDistance) override;
};

#endif