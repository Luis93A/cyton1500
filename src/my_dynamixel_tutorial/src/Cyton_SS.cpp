#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <cstdlib>

#include "ros/ros.h"
#include "dynamixel_controllers/SetSpeed.h"
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/Int32MultiArray.h"
#include "std_msgs/Float64.h"
#include <std_msgs/Float64.h>

using namespace std;

std_msgs::Float32MultiArray CJS_D;

ros::ServiceClient joint0, joint1, joint2, joint3, joint4, joint5, joint6 , joint7; 

void callback(const std_msgs::Float32MultiArray::ConstPtr& msg)
{
	//int length = 7;  				// establish size of array
    
/*
	double max = msg->data[0];   	// start with max = first element
    double min = msg->data[0];   	// start with min = first element
	
    for(int i = 1; i<length; i++)
    {
		if(abs(msg->data[i]) > max)
		{
				max = abs(msg->data[i]);
		}
    }
    
    for(int i = 1; i<length; i++)
    {
		if(abs(msg->data[i]) < min)
		{
				min = abs(msg->data[i]);
		}
    } 
*/ 


        dynamixel_controllers::SetSpeed srv0;
	dynamixel_controllers::SetSpeed srv1;
	dynamixel_controllers::SetSpeed srv2;
	dynamixel_controllers::SetSpeed srv3;
	dynamixel_controllers::SetSpeed srv4;
	dynamixel_controllers::SetSpeed srv5;
	dynamixel_controllers::SetSpeed srv6;
	//dynamixel_controllers::SetSpeed srv7; /*EE*/
	
	double t = 2; /* time of execution in seconds*/
	
	double v0, v1, v2, v3, v4, v5, v6; // v7;

/** Speed calculation */	
	v0 = 0.5;
	v1 = 0.5;
	v2 = 0.5;
	v3 = 0.5;
	v4 = 0.5;
	v5 = 0.5;
	v6 = 0.5;
	
	
	srv0.request.speed = v0;
	srv1.request.speed = v1;
	srv2.request.speed = v2;
	srv3.request.speed = v3;
	srv4.request.speed = v4;
	srv5.request.speed = v5;
	srv6.request.speed = v6;
	//srv7.request.speed = (msg->data[7])/t;

/*Set speed for each joint*/
	joint0.call(srv0);
	joint1.call(srv1);
	joint2.call(srv2);
	joint3.call(srv3);
	joint4.call(srv4);
	joint5.call(srv5);
	joint6.call(srv6);
	//joint7.call(srv7);
	
}




int main(int argc, char **argv)
{
    ros::init(argc, argv, "cyton_SS");
   	ros::NodeHandle nh;
   	//ros::Rate loop_rate(50);
	ros::Subscriber sub = nh.subscribe ("/IKCJ_D", 1, callback);

	joint0 = nh.serviceClient<dynamixel_controllers::SetSpeed>("/shoulder_roll_position_controller/set_speed");
	joint1 = nh.serviceClient<dynamixel_controllers::SetSpeed>("/shoulder_pitch_position_controller/set_speed");
	joint2 = nh.serviceClient<dynamixel_controllers::SetSpeed>("/shoulder_yaw_position_controller/set_speed");
	joint3 = nh.serviceClient<dynamixel_controllers::SetSpeed>("/elbow_pitch_position_controller/set_speed");
	joint4 = nh.serviceClient<dynamixel_controllers::SetSpeed>("/elbow_yaw_position_controller/set_speed");
	joint5 = nh.serviceClient<dynamixel_controllers::SetSpeed>("/wrist_pitch_position_controller/set_speed");
	joint6 = nh.serviceClient<dynamixel_controllers::SetSpeed>("/wrist_roll_position_controller/set_speed");
	//joint7 = nh.serviceClient<dynamixel_controllers::SetSpeed>("/gripper_position_controller/set_speed");

	ros::spin();
	return 0;
}

