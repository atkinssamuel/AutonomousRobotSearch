#include <sensor_msgs/LaserScan.h>
#include <cmath>

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
    for (int i = 200; i < 336; i++)
    {
        minDistance = std::min(minDistance, _laserArray[i]);
    }

    return minDistance;
}

float LaserData::getLeftDistance() 
{
    float leftDistance = 0;
    int leftLasers = 100;
    int leftUsed = 0;
    for (int i = 0; i < leftLasers; i++) {
        if(_laserArray[i] < 100)  {
            leftDistance += _laserArray[i];
            leftUsed++;
        }
    }
    leftDistance = leftDistance /((float) leftUsed);
    return leftDistance;
}

float LaserData::getRightDistance() 
{
    float rightDistance = 0;
    int rightLasers = 539;
    int rightUsed = 0;
    for (int i = rightLasers; i < NUM_LASERS; i++) {
        if(_laserArray[i] < 100)  {
            rightDistance += _laserArray[i];
            rightUsed++;
        }
    }
    rightDistance = rightDistance / ((float)rightUsed);
    return rightDistance;
}
