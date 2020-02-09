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

    _shortTurnThreshold = 1;
    _longTurnThreshold = _shortTurnThreshold * 2;

    _turnVelocity = 0.4;

    _startTime = std::chrono::system_clock::now();
    _turnTime = std::chrono::system_clock::now();
    _timeElapsed = 0;
    _turnTimeElapsed = 0;
    _failureTime = 20;
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
    std::cout << "\n_turnTimeElapsed: " << _turnTimeElapsed;
    
    _timeElapsed = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - _startTime).count();
    _turnTimeElapsed = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - _turnTime).count();

    if (_timeElapsed > _failureTime)
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

        _init = false;
        _left = true;
        _right = false;
        _straighten = false;
        IsFinished = false;
        _turnTime = std::chrono::system_clock::now();
    }
    else if (_left)
    {
        vel.linear.x = 0.0;
        vel.angular.z = _turnVelocity;

        
        if (_turnTimeElapsed > _shortTurnThreshold)
        {
            _init = false;
            _left = false;
            _right = true;
            _straighten = false;
            IsFinished = false;
            _turnTime = std::chrono::system_clock::now();
        }
    }
    else if (_right)
    {
        vel.linear.x = 0.0;
        vel.angular.z = -_turnVelocity;

        if (_turnTimeElapsed > _longTurnThreshold)
        {
            _init = false;
            _left = false;
            _right = false;
            _straighten = true;
            IsFinished = false;
            _turnTime = std::chrono::system_clock::now();
        }
    }
    else if (_straighten)
    {
        vel.linear.x = 0.0;
        vel.angular.z = _turnVelocity;

        if (_turnTimeElapsed > _shortTurnThreshold)
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

