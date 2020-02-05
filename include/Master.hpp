#ifndef MASTER_H
#define MASTER_H

#include <chrono>
#include <geometry_msgs/Twist.h>
#include "IStrategy.hpp"

class Master : public IStrategy
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
    Master();
    geometry_msgs::Twist step(BumperData bumperData, LaserData laserData, OdomData odomData) override;
};

#endif