#include <ros/console.h>
#include "ros/ros.h"
#include <geometry_msgs/Twist.h>
#include <kobuki_msgs/BumperEvent.h>
#include <sensor_msgs/LaserScan.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_datatypes.h>

#include <stdio.h>
#include <stdint.h>
#include <cmath>
#include <chrono>

#include "BumperData.hpp"
#include "LaserData.hpp"
#include "OdomData.hpp"

#include "DemoStrategy.hpp"
#include "MasterStrategy.hpp"
#include "RandomWalkStrategy.hpp"
#include "SpiralStrategy.hpp"
#include "WallFollowStrategy.hpp"
#include "SpinStrategy.hpp"
#include "SimulationDetector.hpp"

#define RAD2DEG(rad) ((rad)*180. / M_PI)
#define DEG2RAD(deg) ((deg)*M_PI / 180.)

using namespace std;

BumperData bumperData;
LaserData laserData;
OdomData odomData;

void bumperCallback(const kobuki_msgs::BumperEvent::ConstPtr &msg)
{
    bumperData.updateState(msg);
}

void laserCallback(const sensor_msgs::LaserScan::ConstPtr &msg)
{
    laserData.updateState(msg);
}

void odomCallback(const nav_msgs::Odometry::ConstPtr &msg)
{
    odomData.updateState(msg);
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

    IStrategy *strategy = new DemoStrategy();

    while (ros::ok() && secondsElapsed <= 480)
    {
        ros::spinOnce();

        vel = strategy->step(bumperData, laserData, odomData);

        vel_pub.publish(vel);

        // The last thing to do is to update the timer.
        secondsElapsed = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - start).count();
        loop_rate.sleep();
    }

    return 0;
}
