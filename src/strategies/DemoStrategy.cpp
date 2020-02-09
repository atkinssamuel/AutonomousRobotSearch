#include <chrono>
#include <kobuki_msgs/BumperEvent.h>
#include "DemoStrategy.hpp"
#include "SwivelStrategy.hpp"

DemoStrategy::DemoStrategy()
{
    _newSwivelStrategy = true;
    _swivelStrategy = false;
    IsFinished = false;
}

bool DemoStrategy::getIsFinished()
{
    return false;
}

geometry_msgs::Twist DemoStrategy::step(BumperData bumperData, LaserData laserData, OdomData odomData)
{
    geometry_msgs::Twist vel;
    if (_newSwivelStrategy)
    {
        strategy = new SwivelStrategy();
        _newSwivelStrategy = false;
        _swivelStrategy = true;
    }

    vel = strategy->step(bumperData, laserData, odomData);
    

    return vel;
};