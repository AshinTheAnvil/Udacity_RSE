#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>
//#include <algorithm> // For std::all_of



// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // TODO: Request a service and pass the velocities to it to drive the robot
   
    ROS_INFO_STREAM("Driving the Robot");

   
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z= ang_z;

}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    int white_pixel = 255;
    bool white_pixel_found = false;
    float v_x = 0;
    float om_z = 0;

    // TODO: Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera

    // Loop through each pixel in the image and check if its equal to the first one
    for (int i = 0; i < img.height * img.step; i+=3) 
	{

        if ((img.data[i+1] == white_pixel)&&(img.data[i+2]  == white_pixel)&&(img.data[i+3] == white_pixel) )
	//if (std::all_of(&img.data[i], &img.data[i + 3], [white_pixel](int value) { return value == white_pixel; }))

	{
            white_pixel_found = true;

	    // Calculate the column index of the pixel
	   
            int column_located = (i % img.step) / 3; // 3 is used for division as RGB has 3 channels

	    if (column_located < img.step / 3) 
	    {
            // To Left
            v_x = 0.0;
            om_z = 0.3;
	    }
	    else if (column_located > img.step * 2 / 3)
	    {
            // To Right
            v_x = 0.0;
            om_z = -0.3;
	    }
	    else 
	    {
            // drive straight
            v_x = 0.3;
    	    om_z = 0.0;
	    }

            break;
        }
	drive_robot(v_x, om_z);

       }
   // Stop the robot if no white pixel is found
    if (white_pixel_found==false)
    {
        v_x = 0.0;
        om_z = 0.0;
    }

 
    
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
