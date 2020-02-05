#include <chrono>
#include <kobuki_msgs/BumperEvent.h>
#include "Master.hpp"
#include "SpinStrategy.hpp"
#include "SwivelStrategy.hpp"

Master::Master()
{
    _startTime = std::chrono::system_clock::now();
    _secondsElapsed = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - _startTime).count();

    _newSpinStrategy = false;
    _newSwivelStrategy = true;

    _spinStrategy = false;
    _swivelStrategy = false;

}

geometry_msgs::Twist Master::step(BumperData bumperData, LaserData laserData, OdomData odomData)
{
    _secondsElapsed = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - _startTime).count();

    if (_secondsElapsed % 15 == 0 && !_swivelStrategy)
    {
        _newSwivelStrategy = true;
    }

    if (_newSpinStrategy)
    {
        std::cout << "Initializing SpinStrategy \n";
        strategy = new SpinStrategy();
        _newSpinStrategy = false;
        _spinStrategy = true;
    } else if(_newSwivelStrategy)
    {
        std::cout << "Initializing SwivelStrategy \n";
        strategy = new SwivelStrategy();
        _newSwivelStrategy = false;
        _swivelStrategy = true;
    }
        
    vel = strategy->step(bumperData, laserData, odomData);
    return vel;
};