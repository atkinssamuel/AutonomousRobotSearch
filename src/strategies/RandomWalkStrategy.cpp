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

    angular = 0;
    linear = 0;
}

geometry_msgs::Twist RandomWalkStrategy::step(BumperData bumperData, LaserData laserData, OdomData odomData)
{
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
            _randomTurnTimeThreshold = (rand() % 8) / 2;
        }
    }
    else if (_turningRandom)
    {
        // Get the current time
        std::chrono::time_point<std::chrono::system_clock> currTime = std::chrono::system_clock::now();

        // Get how much time has elapsed since we started randomly tuning
        //std::chrono::duration_cast<std::chrono::seconds>(currTime - _randomTurnStartTime).count();
        // If we have been turning for longer than our threshold, go into the moving forward loop
        //

        if (minLaserDistance < 0.5 || minLaserDistance > 100)
        {
            _turningRandom = false;
            _turning = true;
        }
        if (std::chrono::duration_cast<std::chrono::seconds>(currTime - _randomTurnStartTime).count() > _randomTurnTimeThreshold)
        {
            angular = 0.0;
            linear = 0.25;

            int gauss = rand() % 100;

            if (gauss < 100)
            {
                linear = 0.2;
                angular = -0.06;
                if (laserData.getRightDistance() > laserData.getLeftDistance())
                    angular = 0.05;
            }
            else
            {
                linear = 0.25;
                angular = 0;
            }

            _movingForward = true;
            _turningRandom = false;
            _turning = false;
        }
    }
    else if (_movingForward)
    {
        bool rightTooClose = (laserData.getLeftDistance() < 0.6);
        bool leftTooClose = (laserData.getRightDistance() < 0.6);

        if (minLaserDistance < 0.5 || minLaserDistance > 100 || rightTooClose || leftTooClose)
        {
            float rightDist = laserData.getRightDistance();
            float leftDist = laserData.getLeftDistance();
            linear = 0.0;
            angular = 0.4;
            if (leftDist < rightDist)
                angular = -0.4;

            _movingForward = false;
            _turning = true;
        }
    }

    if(linear > 0) {
        bool rightTooClose = (laserData.getLeftDistance() < 0.75);
        bool leftTooClose = (laserData.getRightDistance() < 0.75);
        if (minLaserDistance < 0.75 || minLaserDistance > 100|| rightTooClose || leftTooClose)
        {
            linear = 0.1;
        }

    }

    return vel;
};
