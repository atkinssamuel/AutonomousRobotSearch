#include <ros/console.h>
#include "ros/ros.h"
#include <geometry_msgs/Twist.h>
#include <kobuki_msgs/BumperEvent.h>
#include <sensor_msgs/LaserScan.h>
#include<nav_msgs/Odometry.h>
#include<tf/transform_datatypes.h>

#include <stdio.h>
#include <cmath>

#include <chrono>

#define N_BUMPER (3)
#define RAD2DEG(rad) ((rad) *180./M_PI)
#define DEG2RAD(deg) ((deg) *M_PI /180.)
#define NEWLINE '\n';
#define SPEED 0.1;

using namespace std;
float angular = 0.0;
float linear = 0.1;
float posX = 0.0, posY = 0.0, yaw = 0.0;
uint8_t bumper[3] = {kobuki_msgs::BumperEvent::RELEASED, kobuki_msgs::BumperEvent::RELEASED, kobuki_msgs::BumperEvent::RELEASED};

float minLaserDist = std::numeric_limits<float>::infinity();
int32_t nLasers = 0, desiredNLasers=0, desiredAngle=5;


float desiredYaw = 0.0;
bool turnFlag = false;
bool straightFlag = false;

void bumperCallback(const kobuki_msgs::BumperEvent::ConstPtr& msg)
{
    bumper[msg->bumper] = msg->state;
}

void laserCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
    minLaserDist = std::numeric_limits<float>::infinity();
    nLasers = (msg->angle_max-msg->angle_min)/msg->angle_increment;
    desiredNLasers = desiredAngle*M_PI/(180*msg->angle_increment);
    ROS_INFO("Size of laserscan array:%i and size ofoffset: %i", nLasers, desiredNLasers);

    if(desiredAngle*M_PI/180 < msg->angle_max && -desiredAngle*M_PI/180 > msg->angle_min) 
    {
        for(uint32_t laser_idx = nLasers/2-desiredNLasers; laser_idx < nLasers/2 + desiredNLasers; ++laser_idx)
        {
            minLaserDist=std::min(minLaserDist, msg->ranges[laser_idx]);
        }
    }
    else
    {
        for(uint32_t laser_idx=0; laser_idx < nLasers; ++laser_idx) 
        {
            minLaserDist = std::min(minLaserDist, msg->ranges[laser_idx]);
        }
    }
}

void odomCallback(const nav_msgs::Odometry::ConstPtr& msg) 
{
    posX = msg->pose.pose.position.x;
    posY = msg->pose.pose.position.y;
    yaw = tf::getYaw(msg->pose.pose.orientation);
    tf::getYaw(msg->pose.pose.orientation);
    // ROS_INFO("Position: (%f, %f) Orientation: %f rad or %f degrees.", posX, posY, yaw, RAD2DEG(yaw));
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "image_listener");
    ros::NodeHandle nh;

    ros::Subscriber bumper_sub = nh.subscribe("mobile_base/events/bumper", 10, &bumperCallback);
    ros::Subscriber laser_sub = nh.subscribe("scan", 10, &laserCallback);
    ros::Subscriber odom_sub = nh.subscribe("odom", 1, &odomCallback);

    ros::Publisher vel_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel_mux/input/teleop", 1);

    ros::Rate loop_rate(10);

    geometry_msgs::Twist vel;

    // contest count down timer
    std::chrono::time_point<std::chrono::system_clock> start;
    start = std::chrono::system_clock::now();
    uint64_t secondsElapsed = 0;

    while(ros::ok() && secondsElapsed <= 480) {
        ros::spinOnce();

        bool any_bumper_pressed = false;
        for (uint32_t b_idx = 0; b_idx < N_BUMPER; ++b_idx) {
            any_bumper_pressed |= (bumper[b_idx] == kobuki_msgs::BumperEvent::PRESSED);
        }


        cout << "Min laser distance: " << minLaserDist << NEWLINE;
        cout << "Yaw: " << yaw << NEWLINE;
        cout << "Desired yaw: " << desiredYaw << NEWLINE;
        cout << "Straight flag: " << straightFlag;
        cout << NEWLINE;
        cout << "Turn flag: " << turnFlag;
        cout << NEWLINE;

        // Bump and Run Algorithm:
        // Idea: if any_bumper_pressed, turn and keep going
        // if (any_bumper_pressed) {
        //     linear = 0.0;
        //     angular = 0.0;

        //     vel.linear.x = linear;
        //     vel.angular.z = angular;
        //     vel_pub.publish(vel);
        //     uint64_t startTime = secondsElapsed;
        //     uint64_t currTime;
        //     uint64_t timeDiff = 0;
        //     uint64_t threshold = 10;
        //     while (timeDiff < threshold) {
        //         angular = 0.3;
        //         linear = 0.0;
        //         vel.linear.x = linear;
        //         vel.angular.z = angular;
        //         vel_pub.publish(vel);
        //         currTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now()-start).count();
        //         timeDiff = currTime - startTime;
        //     }
        //     linear = 0.1;
        //     angular = 0;
        // }


        if ((minLaserDist < 0.5 || minLaserDist > 100) && !turnFlag) {
            turnFlag = true;
            straightFlag = false;
        }

        if (minLaserDist > 1 && minLaserDist < 100 && turnFlag) {
            turnFlag = false;
            straightFlag = true;
        }

        if (turnFlag) {
            angular = 0.3;
            linear = 0.0;
        }
        if (straightFlag) {
            angular = 0.0;
            linear = 0.2;
        }

        


        vel.linear.x = linear;
        vel.angular.z = angular;

        vel_pub.publish(vel);

        // The last thing to do is to update the timer.
        secondsElapsed = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now()-start).count();
        loop_rate.sleep();
    }

    return 0;
}
