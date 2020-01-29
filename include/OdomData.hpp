#ifndef ODOMDATA_H
#define ODOMDATA_H

#include <nav_msgs/Odometry.h>
#include <stdint.h>

class OdomData
{
public:
    float PosX;
    float PosY;
    float Yaw;

    void updateState(const nav_msgs::Odometry::ConstPtr &msg);
};

#endif