#ifndef WALLFOLLOW_H
#define WALLFOLLOW_H

#include <chrono>
#include <geometry_msgs/Twist.h>
#include "IStrategy.hpp"

class WallFollow : public IStrategy
{
private:

    bool _front;
    bool _notFront;
    bool _followingWall;
    bool _findWall;
    int _whichWall;

    float _upperBound;
    float _upperUpperBound;
    float _lowerBound;

    float angular;
    float linear;

public:
    WallFollow();

    geometry_msgs::Twist step(BumperData bumperData, LaserData laserData, OdomData odomData) override;
};

#endif

