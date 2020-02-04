#include "ros/ros.h"
#include <gazebo_msgs/LinkStates.h>

#include <chrono>

#include "StraightLine.hpp"
#include "SimulationDetector.hpp"

namespace StraightLine
{

float getAngular()
{
    if (SimulationDetector::isSimulated())
        return 0;
    else
        return 0.1;
}

} // namespace StraightLine