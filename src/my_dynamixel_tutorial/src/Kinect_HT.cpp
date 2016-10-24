#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>

/* General includes*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
/* c++ headers*/
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
/* ROS synchronization headers*/
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <message_filters/time_synchronizer.h>
/* ROS headers*/
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/PointCloud2.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/image_encodings.h>
/*OpenCV headers*/
#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
/* Message publication*/
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Float32MultiArray.h"
#include <geometry_msgs/PoseStamped.h>
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

/* tf*/
#include <tf/transform_listener.h>
/* visualization header*/
#include <visualization_msgs/Marker.h>
	
using namespace std;
	
ros::Publisher EES_D; /* publish end-effector*/
/* publisher declaration*/
ros::Publisher shoulder_roll_joint, shoulder_pitch_joint, shoulder_yaw_joint,
						elbow_pitch_joint, elbow_yaw_joint, wrist_pitch_joint, wrist_roll_joint, gripper_joint;

/*
void callback(const std_msgs::Float32MultiArray::ConstPtr& msg){
	std_msgs::Float64 Joint0, Joint1, Joint2, Joint3, Joint4, Joint5, Joint6, Joint7;


				Joint0.data = msg->data[0];
				Joint1.data = msg->data[1]; 
				Joint2.data = msg->data[2]; 
				Joint3.data = msg->data[3];
				Joint4.data = msg->data[4]; 
				Joint5.data = msg->data[5];
				Joint6.data = msg->data[6];
				Joint7.data = msg->data[7];



	if(Joint0.data == 0 && Joint1.data == 0 && Joint2.data == 0 && Joint3.data == 0 && Joint4.data == 0 && Joint5.data == 0 && Joint6.data == 0 && Joint7.data == 0){
	*/

	/* publisher declaration*/
	/*
	


	a=2;


}
*/

int main(int argc, char** argv){

        ros::init(argc, argv, "Kinect_HT");
	ros::NodeHandle nh;
	
	EES_D = nh.advertise<geometry_msgs::PoseStamped>("/EES_D", 1);	
	/* listener */
	tf::TransformListener listener;
	
	ros::Rate rate(50.0); /* frequency of operation*/
	geometry_msgs::PoseStamped check;
	while (ros::ok())
	{
		// Transforms declared for each joint
		tf::StampedTransform  transform_left_hand;
		try
		{
/* each joint frame to reference frame transforms */
			
			listener.lookupTransform("/left_hand_1", "/openni_depth_frame",ros::Time(0), transform_left_hand);
			
			
		}
			catch (tf::TransformException &ex) 
		{
			ROS_ERROR("%s",ex.what());
			ros::Duration(0.10).sleep();
			continue;
		}
	
/* geometry points declaration for storing 3D coordinates of joints and then published later */
		geometry_msgs::PoseStamped left_hand_pose;
		
		/* EE header stamp and frame id*/
		left_hand_pose.header.stamp = ros::Time::now();
		left_hand_pose.header.frame_id = "/base5";
/* joint position extraction and store*/
		
/* left hand joint*/
		left_hand_pose.pose.position.x = transform_left_hand.getOrigin().x();
		left_hand_pose.pose.position.y = transform_left_hand.getOrigin().y();
		left_hand_pose.pose.position.z = -transform_left_hand.getOrigin().z();
		
/* joint positions publish*/
		
		//left_hand_joint.publish(left_hand_pose);
		
		
	/*	std::cout<<"x :" << left_hand_pose.x <<std::endl;
		std::cout<<"y :" << left_hand_pose.y <<std::endl;
		std::cout<<"z :" << left_hand_pose.z <<std::endl;*/
/////////////////////////////////////////////////////////////////////////////////////////////////
	

/* publisher definition*/
		geometry_msgs::PoseStamped msg;
		
/* EE header stamp and frame id*/
		msg.header.stamp = ros::Time::now();
		msg.header.frame_id = "/base1";
		
/* EE Position */
		/*msg.pose.position.x=(left_hand_pose.pose.position.x*0.032+left_hand_pose.pose.position.y*-0.360+left_hand_pose.pose.position.z*-0.932+1.593);
		msg.pose.position.y=(left_hand_pose.pose.position.x*-0.951+left_hand_pose.pose.position.y*0.275+left_hand_pose.pose.position.z*-0.139+0.092);
		msg.pose.position.z=(left_hand_pose.pose.position.x*0.307+left_hand_pose.pose.position.y*0.891+left_hand_pose.pose.position.z*-0.334+1.298);
*/
		msg.pose.position.x = -left_hand_pose.pose.position.z+1.56; //+ 0.002548;
		msg.pose.position.y = left_hand_pose.pose.position.x-0.7;//-0.565;//+ 0.93456;
		msg.pose.position.z = -left_hand_pose.pose.position.y+0.788; //+ 0.614;  
		


		
		//if (msg.pose.position.x == check.pose.position.x) { msg.pose.position.x= 1230;}
		//cout<< "ms"<< msg.pose.position.x<<endl;
		//cout<< "ch"<< check.pose.position.x<<endl;
/* EE Orientation */
		msg.pose.orientation.x = 1.0; 
		msg.pose.orientation.y = 0; 
		msg.pose.orientation.z = 0;
		msg.pose.orientation.w = 0;   
	
		check.pose.position.x=msg.pose.position.x;
		
/* EE Publish */
		EES_D.publish(msg);
		
		
		//ros::spinOnce();
		cout<<"xr--> "<<msg.pose.position.x<<"  yr--> "<<msg.pose.position.y<<"  zr--> "<<msg.pose.position.z<<endl;
		cout<<"xk--> "<<left_hand_pose.pose.position.x<<"  yk--> "<<left_hand_pose.pose.position.y<<"  zk--> "<<left_hand_pose.pose.position.z<<endl;
		rate.sleep();

	}
	//ros::Publisher left_hand_joint = nh.advertise<geometry_msgs::Point>("left_hand_joint", 1);
	
	//ros::Subscriber sub = nh.subscribe ("/CJSS", 1, callback);
	
	ros::spin();
	
	return 0;
}
