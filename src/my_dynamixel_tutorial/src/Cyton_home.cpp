#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>

// Message publication
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/Float64.h"
#include <std_msgs/Float64.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <dynamixel_controllers/SetSpeed.h>


///////////////////////////
#define SHM_SIZE 1024
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <errno.h>

#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/ioctl.h>


using namespace std;
	
/* publisher declaration*/
ros::Publisher shoulder_roll_joint, shoulder_pitch_joint, shoulder_yaw_joint,
						elbow_pitch_joint, elbow_yaw_joint, wrist_pitch_joint, wrist_roll_joint, gripper_joint;



int main(int argc, char** argv){

    ros::init(argc, argv, "arm_joints");
	ros::NodeHandle nh;
	
	
	// publisher declaration
	shoulder_roll_joint = nh.advertise<std_msgs::Float64>("/shoulder_roll_position_controller/command", 1);
	shoulder_pitch_joint = nh.advertise<std_msgs::Float64>("/shoulder_pitch_position_controller/command", 1);
	shoulder_yaw_joint = nh.advertise<std_msgs::Float64>("/shoulder_yaw_position_controller/command", 1);
	elbow_pitch_joint = nh.advertise<std_msgs::Float64>("/elbow_pitch_position_controller/command", 1);
	elbow_yaw_joint = nh.advertise<std_msgs::Float64>("/elbow_yaw_position_controller/command", 1);
	wrist_pitch_joint = nh.advertise<std_msgs::Float64>("/wrist_pitch_position_controller/command", 1);
	wrist_roll_joint = nh.advertise<std_msgs::Float64>("/wrist_roll_position_controller/command", 1);
	gripper_joint = nh.advertise<std_msgs::Float64>("/gripper_position_controller/command", 1);
	
	std_msgs::Float64 Joint0, Joint1, Joint2, Joint3, Joint4, Joint5, Joint6, Joint7;
		
	int i=1;	
	while(i<5){	
	ros::Rate rate(30.0);
				Joint0.data =0.0;
				Joint1.data =0.0; 
				Joint2.data =0.0; 
				Joint3.data =1;
				Joint4.data =0.0; 
				Joint5.data =0.0;
				Joint6.data =0.0;
				Joint7.data = -2;

				/*Joint0.data =2.58247;
				Joint1.data =-1.06587; 
				Joint2.data =0.167402; 
				Joint3.data =-0.497634;
				Joint4.data =-1.55398; 
				Joint5.data =1.4901;
				Joint6.data =-1.17537;*/
				//Joint7.data = -2;
 

				shoulder_roll_joint.publish(Joint0);
				shoulder_pitch_joint.publish(Joint1);
				shoulder_yaw_joint.publish(Joint2);
				elbow_pitch_joint.publish(Joint3);
				elbow_yaw_joint.publish(Joint4);
				wrist_pitch_joint.publish(Joint5);
				wrist_roll_joint.publish(Joint6);
				gripper_joint.publish(Joint7);
			i=i+1;
		rate.sleep();
		}
	
				/***/
		/** FALTA controlar a velocidade **/
				/***/
	return 0;
}

