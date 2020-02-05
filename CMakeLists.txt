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
	src/DemoStrategy.cpp
	src/SpinStrategy.cpp
	src/BumperData.cpp
	src/LaserData.cpp
	src/Master.cpp
	src/OdomData.cpp
	src/RandomWalkStrategy.cpp
	src/Spiral.cpp
	src/SimulationDetector.cpp
	src/SwivelStrategy.cpp
)
target_link_libraries(contest1 ${catkin_LIBRARIES} ${OpenCV_LIB})

