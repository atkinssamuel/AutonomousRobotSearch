#include <chrono>
#include <kobuki_msgs/BumperEvent.h>
#include "MasterStrategy.hpp"
#include "SwivelStrategy.hpp"
#include "RandomWalkStrategy.hpp"

MasterStrategy::MasterStrategy()
{
    _startTime = std::chrono::system_clock::now();
    _lastScanTime = std::chrono::system_clock::now();
    _lastToggleTime = std::chrono::system_clock::now();
    _timeSinceToggle = 0;
    _timeSinceScan = 0;

    _newScan = true;
    _newRandomWalk = false;

    _scan = false;
    _randomWalk = false;
}

geometry_msgs::Twist MasterStrategy::step(BumperData bumperData, LaserData laserData, OdomData odomData)
{
    std::cout << "\n\n_newScan: " << _newScan;
    std::cout << "\n_newRandomWalk: " << _newRandomWalk;
    std::cout << "\n_scan: " << _scan;
    std::cout << "\n_randomWalk: " << _randomWalk;

    _timeSinceScan = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - _lastScanTime).count();
    _timeSinceToggle = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - _lastToggleTime).count();

    if (_newRandomWalk)
    {
        std::cout << "Initializing Random Walk \n";
        strategy = new RandomWalkStrategy();
        _newRandomWalk = false;
        _randomWalk = true;
    }
    else if (_newScan)
    {
        std::cout << "Initializing Scan \n";
        strategy = new SwivelStrategy();
        strategy->IsFinished = false;

        _newScan = false;
        _newRandomWalk = false;
        _scan = true;
        _randomWalk = false;
    }

    if (_timeSinceScan > 10 && !_newScan && !_scan)
    {
        _newScan = true;
        _newRandomWalk = false;
        _scan = false;
        _randomWalk = false;
    }

    if (_scan)
    {
        _lastScanTime = std::chrono::system_clock::now();
        if (strategy->IsFinished)
        {
            _newScan = false;
            _newRandomWalk = true;
            _scan = false;
            _randomWalk = false;
        }
    }

    vel = strategy->step(bumperData, laserData, odomData);

    return vel;
};