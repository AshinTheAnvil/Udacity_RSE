#!/bin/sh
xterm -e " roslaunch turtlebot_gazebo homeservice_world.launch " &
sleep 5

xterm -e " roslaunch turtlebot_gazebo amcl_demo_homeservice.launch " &
sleep 5

xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch " &

sleep 5

xterm -e " roslaunch add_markers add_markers.launch" &
sleep 5
xterm -e " roslaunch pick_objects pick_objects.launch "

