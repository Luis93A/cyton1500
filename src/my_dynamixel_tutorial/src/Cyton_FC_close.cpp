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
int ord=0;

ros::Publisher gripper_joint;
ros::ServiceClient joint0;

void callback(const dynamixel_msgs::JointState::ConstPtr& gripper_feedback, const geometry_msgs::PoseStampedConstPtr& FSR, const geometry_msgs::PoseStampedConstPtr& Control_ord){

	std_msgs::Float64 Joint7;
	double FSR1 , FSR2;

	int action;
	double current_pos; current_pos = gripper_feedback->current_pos;

	FSR1 = FSR->pose.position.x;
	FSR2 = FSR->pose.position.y;
	action = Control_ord->pose.position.x;

	cout<<FSR1<<"--" <<FSR2 <<"--" << current_pos << endl;

	
if(action == 9) {return;}
}


int main(int argc, char** argv)
{
 	ros::init(argc, argv, "Cyton_FC_Close");
	ros::NodeHandle nh;

	
	message_filters::Subscriber<dynamixel_msgs::JointState> joint7_sub(nh, "/gripper_position_controller/state", 1); //_registered
	message_filters::Subscriber<geometry_msgs::PoseStamped> FSR_sub(nh, "/FSR_val", 1); //_registered
	message_filters::Subscriber<geometry_msgs::PoseStamped> ord_sub(nh, "/Fcontrol", 1);

	typedef sync_policies::ApproximateTime<dynamixel_msgs::JointState, geometry_msgs::PoseStamped, geometry_msgs::PoseStamped> MySyncPolicy; 

	Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), joint7_sub, FSR_sub, ord_sub);

	sync.registerCallback(boost::bind(&callback, _1, _2, _3));

	joint0 = nh.serviceClient<dynamixel_controllers::SetSpeed>("/gripper_position_controller/set_speed");

	gripper_joint = nh.advertise<std_msgs::Float64>("/gripper_position_controller/command", 1);

	ordem = nh.advertise<geometry_msgs::PoseStamped>("/fb_close", 1);

	ros::spin();
	
	return 0;
}



