#include <sensor_msgs/LaserScan.h>

#include "LaserData.hpp"

LaserData::LaserData()
{
    _laserArray = new float[NumLasers];
}

void LaserData::updateState(const sensor_msgs::LaserScan::ConstPtr &msg)
{
    // TODO use a memory copy method instead for performance
    for (int i = 0; i < NumLasers; i++)
    {
        _laserArray[i] = msg->ranges[i];
    }
}

float LaserData::getMinDistance()
{
    float minDistance = std::numeric_limits<float>::infinity();
    for (int i = 0; i < NumLasers; i++)
    {
        minDistance = std::min(minDistance, _laserArray[i]);
    }

    return minDistance;
}
