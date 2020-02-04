#include <chrono>
#include <kobuki_msgs/BumperEvent.h>
#include "SpinStrategy.hpp"

SpinStrategy::SpinStrategy()
{
    _init = true;
    _spin = false;
    _finished = false;
}

geometry_msgs::Twist SpinStrategy::step(BumperData bumperData, LaserData laserData, OdomData odomData)
{
    geometry_msgs::Twist vel;
    float _finalAngle;

    std::chrono::time_point<std::chrono::system_clock> _startTime;

    uint64_t _angleThreshold;
    uint64_t _secondsElapsed;
    uint64_t _holdoutTime;

    float minLaserDistance = laserData.getMinDistance();

    if(_init)
    {
        vel.linear.x = 0.0;
        vel.angular.z = 0.0;

        _finalAngle = odomData.Yaw;

        _startTime = std::chrono::system_clock::now();
        _secondsElapsed = 0;
        _holdoutTime = 2;
        _angleThreshold = 0.5;

        _init = false;
        _spin = true;
        _finished = false;
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

        if (_secondsElapsed > _holdoutTime && abs(odomData.Yaw - _finalAngle) < _angleThreshold && 0)
        {
            _init = false;
            _spin = false;
            _finished = true;
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