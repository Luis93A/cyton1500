
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
/* tf*/
#include <tf/transform_listener.h>
/* visualization header*/
#include <visualization_msgs/Marker.h>
	
using namespace std;
	
ros::Publisher Tpoints; /* publish end-effector*/

double getRand(double fmax, double fmin)
{
	const long max_rand = 1000000L;

    srandom(time(NULL));
    double randx;

    randx = fmin + ( fmax - fmin) * (random() % max_rand) / max_rand;
    return randx;
}	
	
	
int main(int argc, char** argv){

	ros::init(argc, argv, "cyton_EE");
	
	ros::NodeHandle nh;
	ros::Rate loop_rate(30);
	
/* data publish for further processing */
	Tpoints = nh.advertise<geometry_msgs::PoseStamped>("/Tpoints", 1);	
	
	while (ros::ok())
	{
/* publisher definition*/
		geometry_msgs::PoseStamped msg;
		
/* EE header stamp and frame id*/
		msg.header.stamp = ros::Time::now();
		msg.header.frame_id = "/base1";
		
/* EE Position */
		msg.pose.position.x = 0.05;//getRand(-0.40, 0.40); 
		msg.pose.position.y = -0.13;//getRand(-0.4, 0); 
		msg.pose.position.z = 0.52;//getRand( 0.3,  0.6);  
		



		cout<<"x--> "<<msg.pose.position.x<<"  y--> "<<msg.pose.position.y<<"  z--> "<<msg.pose.position.z<<endl;
		
/* EE Orientation */
		msg.pose.orientation.x = 1.0; 
		msg.pose.orientation.y = 0; 
		msg.pose.orientation.z = 0;
		msg.pose.orientation.w = 0;   
	
/* EE Publish */
		Tpoints.publish(msg);
		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;
}

