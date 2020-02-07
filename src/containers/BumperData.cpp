#include <kobuki_msgs/BumperEvent.h>

#include "BumperData.hpp"

void BumperData::updateState(const kobuki_msgs::BumperEvent::ConstPtr &msg)
{
    _bumperArray[msg->bumper] = msg->state;
}

uint8_t BumperData::getState(uint8_t bumper)
{
    return _bumperArray[bumper];
}

bool BumperData::anyBumperPressed()
{
    for (uint32_t b_idx = 0; b_idx < NumBumpers; ++b_idx)
    {
        if (_bumperArray[b_idx] == kobuki_msgs::BumperEvent::PRESSED)
            return true;
    }
    return false;
}