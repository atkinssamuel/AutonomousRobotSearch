#ifndef SPIRAL_H
#define SPIRAL_H

#include <chrono>
#include <geometry_msgs/Twist.h>
#include "IStrategy.hpp"

class Spiral : public IStrategy
{
private:

    bool _moving;
public:
    Spiral();

    geometry_msgs::Twist step(uint8_t bumper[3], float minLaserDistance) override;
};

#endif
