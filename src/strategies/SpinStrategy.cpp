#include <chrono>
#include <kobuki_msgs/BumperEvent.h>
#include "SpinStrategy.hpp"

SpinStrategy::SpinStrategy()
{
    _spin = true;
    IsFinished = false;

    _startTime = std::chrono::system_clock::now();
    _timeElapsed = 0.0;
    _turnTime = 9.1;
    _turningVelocity = 0.8;
}

bool SpinStrategy::getIsFinished()
{
    return IsFinished;
}

geometry_msgs::Twist SpinStrategy::step(BumperData bumperData, LaserData laserData, OdomData odomData)
{
    std::cout << "\n\nSpinStrategy";
    std::cout << "\n_spin: " << _spin;
    std::cout << "\n_timeElapsed: " << _timeElapsed;

    float minLaserDistance = laserData.getMinDistance();
    _timeElapsed = ((float)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _startTime).count()) / 1000;

    if (_spin)
    {
        vel.linear.x = 0.0;
        vel.angular.z = _turningVelocity;

        if (_timeElapsed > _turnTime)
        {
            _spin = false;
            IsFinished = true;

            vel.linear.x = 0.0;
            vel.angular.z = 0.0;
        }
    }

    return vel;
};