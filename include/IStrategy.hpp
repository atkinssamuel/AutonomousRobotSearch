#ifndef ISTRATEGY_H
#define ISTRATEGY_H

#include <geometry_msgs/Twist.h>

class IStrategy
{
public:
    virtual geometry_msgs::Twist step(uint8_t bumper[3], float minLaserDistance) = 0;
};

#endif