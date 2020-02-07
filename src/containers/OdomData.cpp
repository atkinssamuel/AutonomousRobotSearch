#include <tf/transform_datatypes.h>
#include <nav_msgs/Odometry.h>

#include "OdomData.hpp"

void OdomData::updateState(const nav_msgs::Odometry::ConstPtr &msg)
{
    PosX = msg->pose.pose.position.x;
    PosY = msg->pose.pose.position.y;
    Yaw = tf::getYaw(msg->pose.pose.orientation);
}