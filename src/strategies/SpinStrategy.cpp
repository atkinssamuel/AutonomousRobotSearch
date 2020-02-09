#include <chrono>
#include <kobuki_msgs/BumperEvent.h>
#include "SpinStrategy.hpp"

SpinStrategy::SpinStrategy()
{
    _init = true;
    _spin = false;
    IsFinished = false;


    _startTime = std::chrono::system_clock::now();
    _secondsElapsed = 0;
    _angleThreshold = 0.1;
    _holdoutTime = 2;
    _turningVelocity = 0.6;

}

bool SpinStrategy::getIsFinished()
{
    return IsFinished;
}

geometry_msgs::Twist SpinStrategy::step(BumperData bumperData, LaserData laserData, OdomData odomData)
{
    std::cout << "\n\nSpinStrategy";
    std::cout << "\n_spin: " << _spin;

    float minLaserDistance = laserData.getMinDistance();
    _secondsElapsed = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - _startTime).count();

    if (_init)
    {
        _finalAngle = odomData.Yaw;

        _init = false;
        _spin = true;
        IsFinished = false;
    }
    else if (_spin)
    {
        vel.linear.x = 0.0;
        vel.angular.z = _turningVelocity;


        if ((abs(odomData.Yaw - _finalAngle) < _angleThreshold && _secondsElapsed > _holdoutTime)|| _secondsElapsed > 15)
        {
            _init = false;
            _spin = false;
            IsFinished = true;

            vel.linear.x = 0.0;
            vel.angular.z = 0.0;
        }
    }

    return vel;
};