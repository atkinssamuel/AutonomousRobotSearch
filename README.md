## Simulation Launch Instructions
To begin, make sure that you've sourced ```catkin_ws/devel/setup.bash```, or that your ```.bashrc``` file does so for you. The following commands run the Gazebo simulation, gmapping node and RViz visualization.

* ```roslaunch mie443_contest1 turtlebot_world.launch world:=1```
* ```roslaunch turtlebot_rviz_launchers view_navigation.launch```
* ```roslaunch turtlebot_gazebo gmapping_demo.launch```
* To run the contest code: ```rosrun mie443_contest1 contest1```
* To run the keyboard teleop: ```roslaunch turtlebot_teleop keyboard_teleop.launch```

Make sure that you don't run both the context code and keyboard teleop at the same time, as the messages published by each will interfere with each other.

## Regular Launch Instructions
On laptop 17, run the following commands in separate terminals:

* ```roslaunch turtlebot_bringup minimal.launch```
* ```roslaunch mie443_contest1 gmapping.launch```
* ```roslaunch turtlebot_rviz_launchers view_navigation.launch```
* ```rosrun mie443_contest1 contest1```

## Regenerating Compile Commands
Use the following command to regenerate the compile commands used by VSCode for code linting.
```
catkin_make -DCMAKE_EXPORT_COMPILE_COMMANDS=ON && mv build/compile_commands.json src/mie443_contest1
```
This should be done every time a new file is added to the project.

## Building a Single Package
From time to time it may be useful to build just a single package in your ```catkin_ws/src/``` directory. To do so, run:
```
catkin_make --only-pkg-with-deps <target_package>
```
This sets a variable in ```CMakeCache.txt``` that whitelists the package specified. This whitelist persists between calls to ```catkin_make```, and can only be cleared with the following command:
```
catkin_make -DCATKIN_WHITELIST_PACKAGES=""
```

## Creating a New Code File
To add a new pair of .cpp and .hpp files to the package, add the .cpp file to ```src/``` and the .hpp file to ```include/```. Then, in ```CMakeLists.txt```, append the name of the file to the list of files in the ```add_executable()``` line