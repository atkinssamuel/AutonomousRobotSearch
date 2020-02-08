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
    _angleThreshold = 0.1;
}

geometry_msgs::Twist SwivelStrategy::step(BumperData bumperData, LaserData laserData, OdomData odomData)
{
    if(IsFinished) {
        this->IsFinished = true;
        ROS_INFO("get out %d", IsFinished);
    }
    else if (_init)
    {
        vel.linear.x = 0.0;
        vel.angular.z = 0.0;

        _leftAngle = odomData.Yaw + DEG2RAD(45);
        _rightAngle = odomData.Yaw - DEG2RAD(45);
        _straightenAngle = odomData.Yaw;

        _init = false;
        _left = true;
        _right = false;
        _straighten = false;
        IsFinished = false;
    }
    else if (_left)
    {
        vel.linear.x = 0.0;
        vel.angular.z = 0.1;

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
        vel.angular.z = -0.1;

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
        vel.angular.z = 0.1;

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

