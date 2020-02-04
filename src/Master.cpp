#include <chrono>
#include <kobuki_msgs/BumperEvent.h>
#include "Master.hpp"
#include "SpinStrategy.hpp"

Master::Master()
{
    _newSpinStrategy = true;
    _spinStrategy = false;

}

geometry_msgs::Twist Master::step(BumperData bumperData, LaserData laserData, OdomData odomData, uint64_t secondsElapsed)
{
    if (_newSpinStrategy)
    {
        strategy = new SpinStrategy();
        _newSpinStrategy = false;
        _spinStrategy = true;
    }
    else if (_spinStrategy)
    {
        vel = strategy->step(bumperData, laserData, odomData, secondsElapsed);
    }
        

    return vel;
};