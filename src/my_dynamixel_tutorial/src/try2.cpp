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

ros::Publisher gripper_joint;
ros::ServiceClient joint0;

ros::Publisher ordem;
int ord=1;
std_msgs::Float64 Joint7;
int i= 1;
int vall[20];

double FSR1 , FSR2;
	int action;
	double current_pos;

void callback1(const dynamixel_msgs::JointState::ConstPtr& gripper_feedback){

 current_pos = gripper_feedback->current_pos;
	
}

void callback3(const geometry_msgs::PoseStampedConstPtr& Control_ord){
 	
	action = Control_ord->pose.position.x;

	
}

void callback2(const geometry_msgs::PoseStampedConstPtr& FSR){

	FSR1 = FSR->pose.position.x;
	FSR2 = FSR->pose.position.y;
	cout<<FSR1<<"--" <<FSR2 <<"--" << current_pos << endl;

geometry_msgs::PoseStamped fb_close;
	
	/* EE header stamp and frame id*/
		fb_close.header.stamp = ros::Time::now();
		fb_close.header.frame_id = "/base15";

if ( action == 1){

ord=0;printf("estou aqui\n");
	if(FSR2 < 200){
		
		
		ros::Rate rate(50.0);
		dynamixel_controllers::SetSpeed srv0;
		srv0.request.speed = 1;
		joint0.call(srv0);

		ord=1;		
			
		Joint7.data = -2;
		gripper_joint.publish(Joint7); 
		rate.sleep();
		
	}

}
printf("%d\n", ord);
fb_close.pose.position.x=ord;

ordem.publish(fb_close);



}




int main(int argc, char** argv)
{
 	ros::init(argc, argv, "Cyton_FC_close");
	ros::NodeHandle nh;

	 ros::Subscriber sub1 = nh.subscribe ("/gripper_position_controller/state", 1, callback1);
	 ros::Subscriber sub2 = nh.subscribe ("/FSR_val", 1, callback2);
	 ros::Subscriber sub3 = nh.subscribe ("/Fcontrol", 1, callback3);

	

	joint0 = nh.serviceClient<dynamixel_controllers::SetSpeed>("/gripper_position_controller/set_speed");

	gripper_joint = nh.advertise<std_msgs::Float64>("/gripper_position_controller/command", 1);

	
	ordem = nh.advertise<geometry_msgs::PoseStamped>("/fb_close", 1);

	ros::spin();
	
	return 0;
}



