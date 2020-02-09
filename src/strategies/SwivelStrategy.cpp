#include <chrono>
#include <ros/console.h>
#include "ros/ros.h"
#include <kobuki_msgs/BumperEvent.h>
#include "SwivelStrategy.hpp"

#define RAD2DEG(rad) ((rad)*180. / M_PI)
#define DEG2RAD(deg) ((deg)*M_PI / 180.)

SwivelStrategy::SwivelStrategy()
{
    _init = true;
    _left = false;
    _right = false;
    _straighten = false;
    IsFinished = false;
    _angleThreshold = DEG2RAD(10);
    _startTime = std::chrono::system_clock::now();
    _timeElapsed = 0;

}

bool SwivelStrategy::getIsFinished()
{
    return SwivelStrategy::IsFinished;
}

geometry_msgs::Twist SwivelStrategy::step(BumperData bumperData, LaserData laserData, OdomData odomData)
{
    std::cout << "\n\nSwivelStrategy";
    std::cout << "\n_init: " << _init;
    std::cout << "\n_left: " << _left;
    std::cout << "\n_right: " << _right;
    std::cout << "\n_straighten: " << _straighten;
    std::cout << "\n_timeElapsed: " << _timeElapsed;


    _timeElapsed = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - _startTime).count();

    if (_timeElapsed > 15)
    {
         _init = false;
        _left = false;
        _right = false;
        _straighten = false;
        IsFinished = true;
    }

    if (_init)
    {
        vel.linear.x = 0.0;
        vel.angular.z = 0.0;

        _leftAngle = odomData.Yaw + DEG2RAD(45);
        _rightAngle = odomData.Yaw - DEG2RAD(45);
        _straightenAngle = odomData.Yaw + DEG2RAD(5);

        _init = false;
        _left = true;
        _right = false;
        _straighten = false;
        IsFinished = false;
    }
    else if (_left)
    {
        vel.linear.x = 0.0;
        vel.angular.z = 0.3;

        if (abs(odomData.Yaw - _leftAngle) < _angleThreshold)
        {
            _init = false;
            _left = false;
            _right = true;
            _straighten = false;
            IsFinished = false;
        }
    }
    else if (_right)
    {
        vel.linear.x = 0.0;
        vel.angular.z = -0.3;

        if (abs(odomData.Yaw - _rightAngle) < _angleThreshold)
        {
            _init = false;
            _left = false;
            _right = false;
            _straighten = true;
            IsFinished = false;
        }
    }
    else if (_straighten)
    {
        vel.linear.x = 0.0;
        vel.angular.z = 0.3;

        if (abs(odomData.Yaw - _straightenAngle) < _angleThreshold)
        {
            vel.linear.x = 0.0;
            vel.angular.z = 0.0;
            _init = false;
            _left = false;
            _right = false;
            _straighten = false;
            IsFinished = true;
        }
    }

    return vel;
};

