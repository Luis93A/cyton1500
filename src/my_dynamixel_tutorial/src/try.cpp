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
/* ROS synchronization headers */
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <message_filters/time_synchronizer.h>
/* dYnamixel */
#include "dynamixel_controllers/SetSpeed.h"
#include "dynamixel_controllers/SetComplianceSlope.h"
#include "dynamixel_msgs/JointState.h"
#include "dynamixel_msgs/MotorStateList.h"
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

/* dYnamixel */
#include "dynamixel_controllers/SetSpeed.h"
#include "dynamixel_controllers/SetComplianceSlope.h"
#include "dynamixel_msgs/JointState.h"
#include "dynamixel_msgs/MotorStateList.h"

#include <sensor_msgs/JointState.h>

#include "tf/transform_listener.h"
#include "tf/message_filter.h"
#include "message_filters/subscriber.h"


#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <stdio.h>                                         // for in-/output
#include <string.h>                                        // strcat
#include <fcntl.h>                                         // for 'O_RDONLY' deklaration
#include <termios.h>                                       // for serial

//Include system headers
#include <cstring>
#include <iostream>
#include <cstdio>

#include <sstream>
//#include <math.h>
//#include <algorithm>

#include <vector>

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
using namespace sensor_msgs;
using namespace message_filters;

ros::Publisher ordem;
int ord = 0;
int oo, oc;

void callback1(const geometry_msgs::PoseStampedConstPtr& fb_op){


	geometry_msgs::PoseStamped f_control;
	
	/* EE header stamp and frame id*/
	f_control.header.stamp = ros::Time::now();
	f_control.header.frame_id = "/base12";

oo = fb_op->pose.position.x;
if (oo == 0) { ord=0;}
else {ord =1 ;}
	printf("%d\n", ord);
	f_control.pose.position.x=ord;
	
	ordem.publish(f_control);
}


void callback2(const geometry_msgs::PoseStampedConstPtr& fb_cl){


	geometry_msgs::PoseStamped f_control;
	
	/* EE header stamp and frame id*/
	f_control.header.stamp = ros::Time::now();
	f_control.header.frame_id = "/base12";

oc = fb_cl->pose.position.x;
if (oc == 0) { ord=1;}
else {ord = 0;}
	printf("%d\n", ord);
	f_control.pose.position.x=ord;

	ordem.publish(f_control); 
}




int main(int argc, char** argv)
{
 	ros::init(argc, argv, "Cyton_FC_control");
	ros::NodeHandle nh;
ros::Rate rate(50);
	
 ros::Subscriber sub1 = nh.subscribe ("/fb_open", 1, callback1);
ros::Subscriber sub2 = nh.subscribe ("/fb_close", 1, callback2);



	ordem = nh.advertise<geometry_msgs::PoseStamped>("/Fcontrol", 1);

	ros::spin();
	
	return 0;
}



