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
    std::chrono::time_point<std::chrono::system_clock> _scanStartTime;

    uint64_t _timeSinceScan;
    uint64_t _timeSinceToggle;
    uint64_t _scanFrequency;

    IStrategy *strategy;

    bool _initFirstSpin;
    bool _newScan;
    bool _newRandomWalk;

    bool _firstSpin;
    bool _scan;
    bool _randomWalk;



    bool IsFinished;

public:
    MasterStrategy();
    geometry_msgs::Twist step(BumperData bumperData, LaserData laserData, OdomData odomData) override;
    bool getIsFinished();
};

#endif
