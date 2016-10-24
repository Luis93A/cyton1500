// General includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
// c++ headers
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
// ROS synchronization headers
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <message_filters/time_synchronizer.h>
// ROS headers
#include <ros/ros.h>

/* Message publication */
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/Float64.h"
#include <std_msgs/Float64.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Twist.h>
#include <dynamixel_controllers/SetSpeed.h>
#include "std_msgs/String.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Int8.h"
#include "std_msgs/Empty.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/PoseStamped.h"
#include <geometry_msgs/PointStamped.h>



#include <iostream>


using namespace std;
using namespace message_filters;

ros::Publisher Tpoints;

void callback(const geometry_msgs::PoseStampedConstPtr& Kht, const geometry_msgs::PoseStampedConstPtr& rp){



	geometry_msgs::PoseStamped Tp_data;
	
	/* EE header stamp and frame id*/
		Tp_data.header.stamp = ros::Time::now();
		Tp_data.header.frame_id = "/base2";

	//double xKinect, yKinect, zKinect;
	
	// point to be calculated
	double xRobot, yRobot, zRobot;

	double xk, yk, zk, xb, yb, zb, xr, yr, zr, xg, yg, zg;
	double xf,yf,zf;


				xk = Kht->pose.position.x;
				yk = Kht->pose.position.y; 
				zk = Kht->pose.position.z; 

				/*xb = bp->pose.position.x;
				yb = bp->pose.position.y; 
				zb = bp->pose.position.z; */

				xr = rp->pose.position.x;
				yr = rp->pose.position.y; 
				zr = rp->pose.position.z; 

				/*xg = gp->pose.position.x;
				yg = gp->pose.position.y; 
				zg = gp->pose.position.z; */


cout<<"sdfsdfsdfsdfsdfsdsfsdfsdfsdfsdf"<<xg<<endl;

		 if( xr != 9) {
			xf=xr; yf=yr; zf=zr;}
	else { xf=xk; yf=yk; zf=zk;}

	
	

	
	// data Printing
/*
	std::cout << "\n The input kinect Coordinate is  : \t" ;
	printf ("pointKinect-----> < %0.3f, %0.3f, %0.3f >\n", xKinect, yKinect, zKinect);
	std::cout << "\n The corresponding Robot Coordinate is  : \t" ;
	printf ("pointRobot-----> < %0.3f, %0.3f, %0.3f >\n", xRobot, yRobot, zRobot);	
*/

/*
std::cout <<"The Estimated Rotation and translation matrices (using getTransformation function) are : \n" << std::endl;
printf ("\n");
printf (" | %6.3f %6.3f %6.3f | \n", transformKC (0,0), transformKC (0,1), transformKC (0,2));
printf ("R = | %6.3f %6.3f %6.3f | \n",transformKC (1,0), transformKC (1,1),transformKC (1,2));
printf (" | %6.3f %6.3f %6.3f | \n", transformKC (2,0), transformKC (2,1), transformKC (2,2));
printf ("\n");
printf ("t = < %0.3f, %0.3f, %0.3f >\n",transformKC (0,3), transformKC (1,3), transformKC (2,3));
*/


Tp_data.pose.position.x=xf;
Tp_data.pose.position.y=yf;
Tp_data.pose.position.z=zf;

Tpoints.publish(Tp_data);
cout<<"sdfsdfsdfsdfsdfsdsfsdfsdfsdfsdf"<<Tp_data<<endl;
}


int main(int argc, char **argv){

ros::init(argc, argv, "Cyton_EE");
ros::NodeHandle nh;


message_filters::Subscriber<geometry_msgs::PoseStamped> KHTP_sub (nh, "/EES_D", 1); //_registered
//message_filters::Subscriber<geometry_msgs::PoseStamped> BP_sub (nh, "/pos_blue", 1); //_registered
message_filters::Subscriber<geometry_msgs::PoseStamped> RP_sub (nh, "/pos_red", 1); //_registered
//message_filters::Subscriber<geometry_msgs::PoseStamped> GP_sub (nh, "/pos_green", 1); //_registered

typedef sync_policies::ApproximateTime<geometry_msgs::PoseStamped, geometry_msgs::PoseStamped> MySyncPolicy;

Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), KHTP_sub, RP_sub);
														
sync.registerCallback(boost::bind(&callback, _1, _2));

Tpoints = nh.advertise<geometry_msgs::PoseStamped>("/Tpoints", 1);

ros::spin();

return 0;
}
 


