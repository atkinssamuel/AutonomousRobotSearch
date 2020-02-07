#ifndef MASTERSTRATEGY_H
#define MASTERSTRATEGY_H

#include <chrono>
#include <geometry_msgs/Twist.h>
#include "IStrategy.hpp"

class MasterStrategy : public IStrategy
{
private:
    geometry_msgs::Twist vel;
    std::chrono::time_point<std::chrono::system_clock> _startTime;
    std::chrono::time_point<std::chrono::system_clock> _lastScanTime;
    std::chrono::time_point<std::chrono::system_clock> _lastToggleTime;

    uint64_t _timeSinceScan;
    uint64_t _timeSinceToggle;

    IStrategy *strategy;

    bool _newScan;
    bool _newRandomWalk;

    bool _scan;
    bool _randomWalk;

public:
    MasterStrategy();
    geometry_msgs::Twist step(BumperData bumperData, LaserData laserData, OdomData odomData) override;
};

#endif