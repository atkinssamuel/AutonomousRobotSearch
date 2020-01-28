#include <chrono>
#include <ros/console.h>
#include "ros/ros.h"
#include <kobuki_msgs/BumperEvent.h>
#include "RandomWalkStrategy.hpp"

RandomWalk::RandomWalk()
{
    _turning = false;
    _movingForward = true;
    _turningRandom = false;

    _turnTimeThreshold = 10; //seconds
    _randomTurnTimeThreshold = 0; //seconds

    angular = 0;
    linear = 0;
}

geometry_msgs::Twist RandomWalk::step(BumperData bumperData, LaserData laserData)
{
    geometry_msgs::Twist vel;
    float minLaserDistance = laserData.getMinDistance();

    if (_turning)
    {
        vel.linear.x = 0.0;
        vel.angular.z = 1;


        if (minLaserDistance > 1 && minLaserDistance < 100)
        {


            vel.linear.x = 0.0;
            vel.angular.z = 1;

            _movingForward = false;
            _turningRandom = true;
            _turning = false;
            _randomTurnStartTime = std::chrono::system_clock::now();

            // Set some random time to turn
            _randomTurnTimeThreshold = (rand() % 4) + 1;
        }
    }
    else if(_turningRandom) {
        // Get the current time
        vel.angular.z = 1;
        std::chrono::time_point<std::chrono::system_clock> currTime = std::chrono::system_clock::now();

        // Get how much time has elapsed since we started randomly tuning
        //std::chrono::duration_cast<std::chrono::seconds>(currTime - _randomTurnStartTime).count();
        ROS_INFO("here");
        // If we have been turning for longer than our threshold, go into the moving forward loop
        if (std::chrono::duration_cast<std::chrono::seconds>(currTime - _randomTurnStartTime).count() > _randomTurnTimeThreshold) {
            vel.linear.x = 0.0;
            vel.angular.z = 0.0;

            _movingForward = true;
            _turningRandom = false;
            _turning = false;
        }
    }
    else if (_movingForward)
    {
        vel.linear.x = 0.25;
        vel.angular.z = 0.0;

        if (minLaserDistance < 0.5 || minLaserDistance > 100)
        {
            vel.linear.x = 0.0;
            vel.angular.z = 1;

            _movingForward = false;
            _turning = true;
        }
    }

    return vel;
};
