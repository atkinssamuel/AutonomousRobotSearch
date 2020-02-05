#include <chrono> 
#include <ros/console.h>
#include "ros/ros.h"
#include <kobuki_msgs/BumperEvent.h>
#include "WallFollowStrategy.hpp"

WallFollow::WallFollow()
{
    _front = false;
    _notFront = false;
    _followingWall = false;
    _findWall = true;
    // 0 is left wall, 1 is right wall
    _whichWall = 0;
    
    _upperBound = 0.85;
    _upperUpperBound = 1.5;
    _lowerBound = 0.6;

    angular = 0;
    linear = .2;
    done = false;

}


geometry_msgs::Twist WallFollow::step(BumperData bumperData, LaserData laserData, OdomData odomData)
{
    geometry_msgs::Twist vel;
    float minLaserDistance = laserData.getMinDistance();
    float rightLaserDistance = laserData.getRightDistance();
    float leftLaserDistance = laserData.getLeftDistance();
    vel.linear.x = linear;
    vel.angular.z = angular;

    ROS_INFO("Min dist: %f", minLaserDistance);
    
    if(done) {
        return vel;
    }
    
    if (_findWall)
    {

        float distance = leftLaserDistance;
        if(_whichWall) {
            distance = rightLaserDistance;
        }
        bool laserCondition = (distance < 0.5 || distance > 100);
        if (minLaserDistance < 0.5 || minLaserDistance > 100 || laserCondition)
        {
            _whichWall = 1;
            angular = 0.3;
            linear = 0.0;
            if(rightLaserDistance > leftLaserDistance) {
                _whichWall = 0;
                angular = -0.3;
            }

            _findWall = false;
            _front = true;
        }
        ROS_INFO("FINDING WALL");
    }
    else if (_front)
    {


        float distance = leftLaserDistance;
        if(_whichWall) {
            distance = rightLaserDistance;
        }
        bool laserCondition2 = (distance > 0.6 && distance < 100);
        _front = true;
        
        if(minLaserDistance > 0.5 && minLaserDistance < 100 && laserCondition2) {
            _front = false;
            _followingWall = true;
            angular = 0;
            linear = 0.2;
            done = true;
        }

        ROS_INFO("FRONT");

    }
    else if(_notFront) {

    }
    else if (_followingWall)
    {

        angular = 0.0;
        linear = .2;
        if(_whichWall) {
            angular = 0;
        }
        float distance = leftLaserDistance;
        if(_whichWall) {
            distance = rightLaserDistance;
        }

        if(distance > _upperBound && distance < 100) {
       //     _followingWall = false;
     //       _notFront = true;
            //linear = 0.2;
            //angular = 0.0;
            //_followingWall = false;
            //_front = false;
            //_findWall = true;

            _followingWall = true;
            angular = 0.4;
            linear = 0.0;
            if(_whichWall) {
                angular = -0.4;
            }
            done = true;
        }

        else if(distance < 0.6 || distance > 100) {
            _followingWall = true;
            angular = -0.4;
            linear = 0.1;
            if(_whichWall) {
                angular = 0.4;
            }
        }
        
        if(minLaserDistance < 0.5 || minLaserDistance > 100) {
            _front = true;
            linear = 0;
            _followingWall = false;
            angular = -0.3;
            if(_whichWall) {
                angular = 0.3;
            }

        }

        if(minLaserDistance > 0.5 && minLaserDistance < 100) {
            if(distance > _upperUpperBound && distance < 100) {
                linear = 0.2;
                angular = 0.0;
                _followingWall = false;
                _front = false;
                _findWall = true;
            }
        }


        //check if the weird corner thing happned
       // if(leftLaserDistance < minLaserDistance && rightLaserDistance < minLaserDistance) {
       //     _front = true;
       //     linear = 0;
       //     _followingWall = false;
       //     angular = -0.3;
       //     if(_whichWall) {
       //         angular = 0.3;
       //     }

       // }
        ROS_INFO("FOLLOWING WALL");
        ROS_INFO("Distance: %f", distance);
        ROS_INFO("minRight: %f", rightLaserDistance);
        ROS_INFO("minLeft: %f", leftLaserDistance);
        ROS_INFO("angular: %f", angular);
        ROS_INFO("which wall: %d", _whichWall);
        ROS_INFO("");
    }

    return vel;
};
