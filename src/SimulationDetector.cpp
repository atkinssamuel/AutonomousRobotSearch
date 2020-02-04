#include "ros/ros.h"
#include <gazebo_msgs/LinkStates.h>

#include <chrono>

#include "SimulationDetector.hpp"

namespace SimulationDetector
{

bool _isInitialized = false;
bool _isSimulated = false;

void gazeboCallback(const gazebo_msgs::LinkStates::ConstPtr &msg)
{
    _isSimulated = true;
}

bool isSimulated()
{
    if (_isInitialized)
        return _isSimulated;

    // Initialize. Determine whether gazebo is running.

    ros::NodeHandle nh;
    ros::Subscriber gazebo_sub = nh.subscribe("gazebo/link_states", 10, &gazeboCallback);

    ros::Rate loop_rate(10);
    std::chrono::time_point<std::chrono::system_clock> start;
    start = std::chrono::system_clock::now();
    uint64_t secondsElapsed = 0;

    while (ros::ok() && secondsElapsed <= 1)
    {
        ros::spinOnce();

        secondsElapsed = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - start).count();
        loop_rate.sleep();
    }
}

} // namespace SimulationDetector