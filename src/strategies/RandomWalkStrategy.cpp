#include <chrono>
#include <ros/console.h>
#include "ros/ros.h"
#include <kobuki_msgs/BumperEvent.h>
#include "RandomWalkStrategy.hpp"

RandomWalkStrategy::RandomWalkStrategy()
{
    _turning = false;
    _movingForward = true;
    _turningRandom = false;

    _turnTimeThreshold = 10;      //seconds
    _randomTurnTimeThreshold = 0; //seconds
    IsFinished = false;

    _linearVelocity = 0.15;
    _angularVelocity = 0.5;

    _maxRandomTurnTime = 2;

    // _wallThreshold = 0.6; *** REAL WORLD OPTIMAL ***
    _wallThreshold = 0.5;

    angular = 0;
    linear = 0;
}

bool RandomWalkStrategy::getIsFinished()
{
    return RandomWalkStrategy::IsFinished;
}

geometry_msgs::Twist RandomWalkStrategy::step(BumperData bumperData, LaserData laserData, OdomData odomData)
{
    std::cout << "\n\nRandomWalkStrategy";
    std::cout << "\n_turning: " << _turning;
    std::cout << "\n_movingForward: " << _movingForward;
    std::cout << "\n_turningRandom: " << _turningRandom;

    geometry_msgs::Twist vel;
    float minLaserDistance = laserData.getMinDistance();
    vel.linear.x = linear;
    vel.angular.z = angular;

    //ROS_INFO("Min dist: %f", minLaserDistance);

    if (_turning)
    {

        if (minLaserDistance > 0.5 && minLaserDistance < 100)
        {
            _movingForward = false;
            _turningRandom = true;
            _turning = false;
            _randomTurnStartTime = std::chrono::system_clock::now();

            // Set some random time to turn
            _randomTurnTimeThreshold = rand() % _maxRandomTurnTime;
        }
    }
    else if (_turningRandom)
    {
        if (minLaserDistance < 0.5 || minLaserDistance > 100)
        {
            _turningRandom = false;
            _turning = true;
        }
        if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - _randomTurnStartTime).count() > _randomTurnTimeThreshold)
        {
            angular = 0.0;
            linear = _linearVelocity;

            int gauss = rand() % 100;

            if (gauss < 100)
            {
                linear = _linearVelocity;
                angular = -0.06;
                if (laserData.getRightDistance() > laserData.getLeftDistance())
                    angular = 0.05;
            }
            else
            {
                linear = _linearVelocity;
                angular = 0;
            }

            _movingForward = true;
            _turningRandom = false;
            _turning = false;
        }
    }
    else if (_movingForward)
    {
        angular = 0.0;
        linear = _linearVelocity;

        bool rightTooClose = (laserData.getLeftDistance() < _wallThreshold);
        bool leftTooClose = (laserData.getRightDistance() < _wallThreshold);

        if (minLaserDistance < 0.5 || minLaserDistance > 100 || rightTooClose || leftTooClose)
        {
            float rightDist = laserData.getRightDistance();
            float leftDist = laserData.getLeftDistance();
            linear = 0.0;
            angular = _angularVelocity;
            if (leftDist < rightDist)
            {
                angular = -_angularVelocity;
            }

            _movingForward = false;
            _turning = true;
        }
    }

    if(linear > 0) {
        bool rightTooClose = (laserData.getLeftDistance() < 0.75);
        bool leftTooClose = (laserData.getRightDistance() < 0.75);
        if (minLaserDistance < 0.75 || minLaserDistance > 100 || rightTooClose || leftTooClose)
        {
            linear = 0.1;
        }

    }


    return vel;
};
