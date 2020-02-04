#include <chrono>
#include <kobuki_msgs/BumperEvent.h>
#include "SpinStrategy.hpp"

SpinStrategy::SpinStrategy()
{
    _init = true;
    _spin = false;
    _finished = false;
}

geometry_msgs::Twist SpinStrategy::step(BumperData bumperData, LaserData laserData, OdomData odomData, uint64_t secondsElapsed)
{
    float minLaserDistance = laserData.getMinDistance();

    if(_init)
    {
        vel.linear.x = 0.0;
        vel.angular.z = 0.0;

        _finalAngle = odomData.Yaw;

        _startTime = std::chrono::system_clock::now();
        _secondsElapsed = 0;
        _holdoutTime = 5;
        _angleThreshold = 0.1;

        _init = false;
        _spin = true;
        _finished = false;

        std::cout << "\nSpinStrategy Begins \n";
    }
    else if(_spin)
    {
        vel.linear.x = 0.0;
        vel.angular.z = 0.3;

        _secondsElapsed = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - _startTime).count();

        std::cout << "Seconds elapsed: " << _secondsElapsed;
        std::cout << "\n"; 
        std::cout << "Odom diff: " << abs(odomData.Yaw - _finalAngle);
        std::cout << "\n";
        std::cout << "angleThreshold: " << _angleThreshold;
        std::cout << "\n";
        std::cout << "holdoutTime: " << _holdoutTime;

        if (_secondsElapsed > _holdoutTime && abs(odomData.Yaw - _finalAngle) < _angleThreshold)
        {
            _init = false;
            _spin = false;
            _finished = true;

            std::cout << "\nSpinStrategy Completed \n";
        }
    } 
    else if(_finished)
    {
        vel.linear.x = 0.0;
        vel.angular.z = 0.0;

        _init = false;
        _spin = false;
        _finished = true;
    }

    return vel;
};