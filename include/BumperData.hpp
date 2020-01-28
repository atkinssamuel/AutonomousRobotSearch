#ifndef BUMPERDATA_H
#define BUMPERDATA_H

#include <stdint.h>
#include <kobuki_msgs/BumperEvent.h>

#define NUM_BUMPERS 3

class BumperData
{
private:
    uint8_t _bumperArray[3] = {kobuki_msgs::BumperEvent::RELEASED, kobuki_msgs::BumperEvent::RELEASED, kobuki_msgs::BumperEvent::RELEASED};

public:
    uint8_t NumBumpers = NUM_BUMPERS;

    void updateState(const kobuki_msgs::BumperEvent::ConstPtr &msg);
    uint8_t getState(uint8_t bumper);
    bool anyBumperPressed();
};

#endif