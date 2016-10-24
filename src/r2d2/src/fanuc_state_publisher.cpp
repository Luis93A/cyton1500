#include <ros/ros.h>
#include <string>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>

double getRand(double fmax, double fmin)
{
	const long max_rand = 1000000L;

    srandom(time(NULL));
    double randx;

    randx = fmin + ( fmax - fmin) * (random() % max_rand) / max_rand;
    return randx;
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;
    ros::Publisher joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
    tf::TransformBroadcaster broadcaster;
    ros::Rate loop_rate(30);

	geometry_msgs::TransformStamped cyton_trans;
	sensor_msgs::JointState joint_state;
	cyton_trans.header.frame_id = "base_link";
	cyton_trans.child_frame_id = "link1";
	
	joint_state.name.resize(8);
	joint_state.position.resize(8);
	joint_state.name[0] ="joint_1";
	joint_state.name[1] ="joint_2";
	joint_state.name[2] ="joint_3";
	joint_state.name[3] ="joint_4";
	joint_state.name[4] ="joint_5";
	joint_state.name[5] ="joint_6";
	

    while (ros::ok()) 
    {
        //update joint_state
	    joint_state.header.stamp = ros::Time::now();
	    joint_state.position[0] = getRand( 2.00, -2.00);
	    joint_state.position[1] = getRand( 2.00, -2.00);
	    joint_state.position[2] = getRand( 2.00, -2.00);
	    joint_state.position[3] = getRand( 2.00, -2.00);
	    joint_state.position[4] = getRand( 2.00, -2.00);
	    joint_state.position[5] = getRand( 2.00, -2.00);

        // update transform
	    // (moving in a circle with radius=2)
	    cyton_trans.header.stamp = ros::Time::now();
	    cyton_trans.transform.translation.x = 0;
	    cyton_trans.transform.translation.y = 0;
	    cyton_trans.transform.translation.z = 0;
	    cyton_trans.transform.rotation = tf::createQuaternionMsgFromYaw(0);
	
	    //send the joint state and transform
	    joint_pub.publish(joint_state);
	    broadcaster.sendTransform(cyton_trans);
	    
	    ros::Duration(0.5).sleep();

	    loop_rate.sleep();
    }


    return 0;
}
