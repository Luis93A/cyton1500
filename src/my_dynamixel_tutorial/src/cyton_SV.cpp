

#include <iostream>
#include "ros/ros.h"
#include "dynamixel_controllers/SetSpeed.h"
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/Float64.h"
#include <std_msgs/Float64.h>

using namespace std;

ros::ServiceClient joint0, joint1, joint2, joint3, joint4, joint5, joint6 , joint7; 
ros::Publisher shoulder_roll_joint, shoulder_pitch_joint, shoulder_yaw_joint,
						elbow_pitch_joint, elbow_yaw_joint, wrist_pitch_joint, wrist_roll_joint, gripper_joint;

int get_max_pos(double *array, int size)
{
    double max=array[0];
    int max_pos=0;

    int i;
    for (i=1; i<size; i++)
    {
        if (max<array[i])
        {
            max=array[i];
            max_pos=i;
        }
    }

    return max_pos;
}
	
void callback(const std_msgs::Float32MultiArray::ConstPtr& msg)
{


std_msgs::Float64 Joint0, Joint1, Joint2, Joint3, Joint4, Joint5, Joint6, Joint7;
	
	int length = 7;  				// establish size of array
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
    
    dynamixel_controllers::SetSpeed srv0;
	dynamixel_controllers::SetSpeed srv1;
	dynamixel_controllers::SetSpeed srv2;
	dynamixel_controllers::SetSpeed srv3;
	dynamixel_controllers::SetSpeed srv4;
	dynamixel_controllers::SetSpeed srv5;
	dynamixel_controllers::SetSpeed srv6;
	//dynamixel_controllers::SetSpeed srv7;
	
	const double w_max [8]={0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
	
	// MX-28 -- 50rpm
    // MX-64 -- 58rpm
	double v0, v1, v2, v3, v4, v5, v6; // v7;
	
	double disp0, disp1, disp2, disp3, disp4, disp5, disp6, disp7;
	
	// displacement calculation
	disp0 = abs (msg->data[7] - msg->data[0]);
	disp1 = abs (msg->data[8] - msg->data[1]);
	disp2 = abs (msg->data[9] - msg->data[2]);
	disp3 = abs (msg->data[10] - msg->data[3]);
	disp4 = abs (msg->data[11] - msg->data[4]);
	disp5 = abs (msg->data[12] - msg->data[5]);
	disp6 = abs (msg->data[13] - msg->data[6]);
	
	double disp[7];
	disp[0]=disp0;
	disp[1]=disp1;
	disp[2]=disp2;
	disp[3]=disp3;
	disp[4]=disp4;
	disp[5]=disp5;
	disp[6]=disp6;
	
	// max displacement index
	int idx = get_max_pos(disp, 7);
	
	// time of execution for maximum displacement according to maximum velocity
	double tMax = (disp[idx])/(w_max[idx]); // get maximum time 
	
	// velocity set for all joints
	v0 = disp0/tMax;
	v1 = disp1/tMax;
	v2 = disp2/tMax;
	v3 = disp3/tMax;
	v4 = disp4/tMax;
	v5 = disp5/tMax;
	v6 = disp6/tMax;
	
	srv0.request.speed = v0;
	srv1.request.speed = v1;
	srv2.request.speed = v2;
	srv3.request.speed = v3;
	srv4.request.speed = v4;
	srv5.request.speed = v5;
	srv6.request.speed = v6;
	//srv7.request.speed = (msg->data[7])/t;

	joint0.call(srv0);
	joint1.call(srv1);
	joint2.call(srv2);
	joint3.call(srv3);
	joint4.call(srv4);
	joint5.call(srv5);
	joint6.call(srv6);

	joint0.call(srv0);
	joint1.call(srv1);
	joint2.call(srv2);
	joint3.call(srv3);
	joint4.call(srv4);
	joint5.call(srv5);
	joint6.call(srv6);
	
	joint0.call(srv0);
	joint1.call(srv1);
	joint2.call(srv2);
	joint3.call(srv3);
	joint4.call(srv4);
	joint5.call(srv5);
	joint6.call(srv6);
	//joint7.call(srv7);
	
	cout<<" joint0 velocity-->>"<<v0<<endl;
	cout<<" joint1 velocity-->>"<<v1<<endl;
	cout<<" joint2 velocity-->>"<<v2<<endl;
	cout<<" joint3 velocity-->>"<<v3<<endl;
	cout<<" joint4 velocity-->>"<<v4<<endl;
	cout<<" joint5 velocity-->>"<<v5<<endl;
	cout<<" joint6 velocity-->>"<<v6<<endl;

	sleep(0.1);

				Joint0.data = msg->data[7];
				Joint1.data = msg->data[8]; 
				Joint2.data = msg->data[9]; 
				Joint3.data = msg->data[10];
				Joint4.data = msg->data[11]; 
				Joint5.data = msg->data[12];
				Joint6.data = msg->data[13];
				//Joint7.data = msg->data[7];


				shoulder_roll_joint.publish(Joint0);
				shoulder_pitch_joint.publish(Joint1);
				shoulder_yaw_joint.publish(Joint2);
				elbow_pitch_joint.publish(Joint3);
				elbow_yaw_joint.publish(Joint4);
				wrist_pitch_joint.publish(Joint5);
				wrist_roll_joint.publish(Joint6);
				//gripper_joint.publish(Joint7);

				shoulder_roll_joint.publish(Joint0);
				shoulder_pitch_joint.publish(Joint1);
				shoulder_yaw_joint.publish(Joint2);
				elbow_pitch_joint.publish(Joint3);
				elbow_yaw_joint.publish(Joint4);
				wrist_pitch_joint.publish(Joint5);
				wrist_roll_joint.publish(Joint6);

				shoulder_roll_joint.publish(Joint0);
				shoulder_pitch_joint.publish(Joint1);
				shoulder_yaw_joint.publish(Joint2);
				elbow_pitch_joint.publish(Joint3);
				elbow_yaw_joint.publish(Joint4);
				wrist_pitch_joint.publish(Joint5);
				wrist_roll_joint.publish(Joint6);

	//sleep(tMax);

}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "cyton_FK");
   	ros::NodeHandle nh;
 
	ros::Subscriber sub = nh.subscribe ("/IKCJ_D", 1, callback);

	joint0 = nh.serviceClient<dynamixel_controllers::SetSpeed>("/shoulder_roll_controller/set_speed");
	joint1 = nh.serviceClient<dynamixel_controllers::SetSpeed>("/shoulder_pitch_controller/set_speed");
	joint2 = nh.serviceClient<dynamixel_controllers::SetSpeed>("/shoulder_yaw_controller/set_speed");
	joint3 = nh.serviceClient<dynamixel_controllers::SetSpeed>("/elbow_pitch_controller/set_speed");
	joint4 = nh.serviceClient<dynamixel_controllers::SetSpeed>("/elbow_yaw_controller/set_speed");
	joint5 = nh.serviceClient<dynamixel_controllers::SetSpeed>("/wrist_pitch_controller/set_speed");
	joint6 = nh.serviceClient<dynamixel_controllers::SetSpeed>("/wrist_roll_controller/set_speed");
	//joint7 = nh.serviceClient<dynamixel_controllers::SetSpeed>("/gripper_position_controller/set_speed");

shoulder_roll_joint = nh.advertise<std_msgs::Float64>("/shoulder_roll_controller/command", 1);
	shoulder_pitch_joint = nh.advertise<std_msgs::Float64>("/shoulder_pitch_controller/command", 1);
	shoulder_yaw_joint = nh.advertise<std_msgs::Float64>("/shoulder_yaw_controller/command", 1);
	elbow_pitch_joint = nh.advertise<std_msgs::Float64>("/elbow_pitch_controller/command", 1);
	elbow_yaw_joint = nh.advertise<std_msgs::Float64>("/elbow_yaw_controller/command", 1);
	wrist_pitch_joint = nh.advertise<std_msgs::Float64>("/wrist_pitch_controller/command", 1);
	wrist_roll_joint = nh.advertise<std_msgs::Float64>("/wrist_roll_controller/command", 1);
	ros::spin();
	return 0;
}


