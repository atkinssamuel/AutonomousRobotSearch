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

    geometry_msgs::Twist step(BumperData bumperData, LaserData laserData) override;
};

#endif
