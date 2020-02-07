cmake_minimum_required(VERSION 2.8)
project(mie443_contest1)

add_compile_options(-std=c++11)

#set(OpenCV_DIR "/usr/share/OpenCV")

find_package(OpenCV 3 REQUIRED)

find_package(catkin REQUIRED COMPONENTS
	cv_bridge
	genmsg
	image_transport
	sensor_msgs
	kobuki_msgs)

generate_messages(DEPENDENCIES sensor_msgs kobuki_msgs)

catkin_package()

include_directories(include ${OpenCV_INCLUDE_DIRS} ${catkin_INCLUDE_DIRS})

# add the publisher example
add_executable(
	contest1
	src/contest1.cpp
	src/containers/BumperData.cpp
	src/containers/LaserData.cpp
	src/containers/OdomData.cpp
	src/strategies/DemoStrategy.cpp
	src/strategies/SpinStrategy.cpp
	src/strategies/MasterStrategy.cpp
	src/strategies/RandomWalkStrategy.cpp
	src/strategies/SpiralStrategy.cpp
	src/strategies/SwivelStrategy.cpp
	src/strategies/WallFollowStrategy.cpp
)
target_link_libraries(contest1 ${catkin_LIBRARIES} ${OpenCV_LIB})

