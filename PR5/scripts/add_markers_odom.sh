#!/bin/sh

xterm -e "source devel/setup.bash;roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 5
xterm -e "source devel/setup.bash;roslaunch turtlebot_gazebo amcl_demo.launch" &
sleep 5
xterm -e "source devel/setup.bash;roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm -e "source devel/setup.bash;roslaunch add_markers add_markers.launch"

