/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2012, Willow Garage, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Willow Garage nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

/* Author: Luís Almeida */

/* HEADERS */

/* ROS */
#include <ros/ros.h>

/* MoveIt! */
#include <moveit/robot_model_loader/robot_model_loader.h>
#include <moveit/robot_model/robot_model.h>
#include <moveit/robot_state/robot_state.h>

/* ROS synchronization headers */
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <message_filters/time_synchronizer.h>

/* Message publication */

/* std */
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/Float64.h"
#include <std_msgs/Float64.h>
/* dynamixel */
#include <dynamixel_controllers/SetSpeed.h>

#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <sstream>
#include<stdio.h>
#include <math.h>
/* Namespaces */
using namespace std;
using namespace sensor_msgs;
using namespace message_filters;

/* Publisher IK_CJ -> Inverse Kinematics Calculated Joint Data */ 
ros::Publisher IKCJ_D;
ros::Publisher sa;
ros::Publisher FK_D;



void callback(const std_msgs::Float32MultiArray::ConstPtr& msg){

	std_msgs::Float32MultiArray CJS_D; /* Current Joint State Data */



	CJS_D.data.clear(); /* Data clear */



	std_msgs::Float64 Joint0, Joint1, Joint2, Joint3, Joint4, Joint5, Joint6, Joint7;
	

				Joint0.data = msg->data[15];
				Joint1.data = msg->data[16]; 
				Joint2.data = msg->data[17]; 
				Joint3.data = msg->data[18];
				Joint4.data = msg->data[19]; 
				Joint5.data = msg->data[20];
				Joint6.data = msg->data[21];
				Joint7.data = msg->data[22];


if ( sqrt( (msg->data[8] * msg->data[8]) + (msg->data[9] * msg->data[9]) + (msg->data[10] * msg->data[10]) ) < 0.75) { //variavel qql com 1 valor a entrar no if seguinte}
	



	if(Joint0.data == 0 && Joint1.data == 0 && Joint2.data == 0 && Joint3.data == 0 && Joint4.data == 0 && Joint5.data == 0 && Joint6.data == 0 && Joint7.data == 0 && msg->data[11] != 0){
/** We will start by instantiating a `RobotModelLoader`_ object, which will look up
	the robot description on the ROS parameter server and construct a :moveit_core:`RobotModel` for us to use.
	.. _RobotModelLoader: http://docs.ros.org/api/moveit_ros_planning/html/classrobot__model__loader_1_1RobotModelLoader.html */

	robot_model_loader::RobotModelLoader robot_model_loader("robot_description");
	robot_model::RobotModelPtr kinematic_model = robot_model_loader.getModel();
	ROS_INFO("Model frame: %s", kinematic_model->getModelFrame().c_str());

/**	Using the :moveit_core:`RobotModel`, we can construct a :moveit_core:`RobotState` that maintains the configuration
	of the robot. We will set all joints in the state to their default values. We can then get a :moveit_core:`JointModelGroup`, 
	which represents the robot model for a particular group, here we are using the "arm" (cyton gamma 1500 Robot Arm). */

	robot_state::RobotStatePtr kinematic_state(new robot_state::RobotState(kinematic_model));
	kinematic_state->setToDefaultValues();
	const robot_state::JointModelGroup* joint_model_group = kinematic_model->getJointModelGroup("arm");
	
	const std::vector<std::string> &joint_names = joint_model_group->getJointModelNames();

/** Here we create a Std vector to retreive the current set of Joint values stored in the state of the arm */
 
	std::vector<double> joint_values;
	kinematic_state->copyJointGroupPositions(joint_model_group, joint_values);

/** For cycle to print Current joint state data in terminal*/
/*
	for(std::size_t i = 0; i < joint_names.size(); ++i){
		ROS_INFO("Joint %s: %f", joint_names[i].c_str(), joint_values[i]);
	}
*/

/* Joint Limits. setJointGroupPositions() does not enforce joint limits by itself, but a call to enforceBounds() will do it.
  /* Set one joint in the right arm outside its joint limit */
  //joint_values[0] = 1.57;
 // kinematic_state->setJointGroupPositions(joint_model_group, joint_values);

  /* Check whether any joint is outside its joint limits */
/*
  ROS_INFO_STREAM("Current state is " << (kinematic_state->satisfiesBounds() ? "valid" : "not valid"));
*/

  /* Enforce the joint limits for this state and check again*/
  kinematic_state->enforceBounds();
/*
  ROS_INFO_STREAM("Current state is " << (kinematic_state->satisfiesBounds() ? "valid" : "not valid"));
*/


/** Forward Kinematics. Now, we can compute forward kinematics for a set of random joint values. Note that we would like to find 
the pose of the "wrist_roll_link" which is the most distal link in the "arm" of the robot. */ 

/* Initialization of joints and storing the current joint state data */

	Eigen::VectorXd joints(8);
	joints << msg->data[0], msg->data[1], msg->data[2], msg->data[3], msg->data[4], msg->data[5], msg->data[6], msg->data[7];
	
	kinematic_state->setJointGroupPositions(joint_model_group, joints);
	
/* end_effector_state declared */
	Eigen::Affine3d end_effector_state;
	
////
geometry_msgs::PoseStamped msg1;
/* EE header stamp and frame id*/
		msg1.header.stamp = ros::Time::now();
		msg1.header.frame_id = "/base7";
		
	end_effector_state = kinematic_state->getGlobalLinkTransform("wrist_roll");

	Eigen::Vector3d current_pose = end_effector_state.translation();

	//ROS_INFO_STREAM("x: " << current_pose(0));
	//ROS_INFO_STREAM("y: " << current_pose(1));
	//ROS_INFO_STREAM("z: " << current_pose(2));

		msg1.pose.position.x = current_pose(0); 
		msg1.pose.position.y = current_pose(1); 
		msg1.pose.position.z = current_pose(2);


		
	/*myfile2 << current_pose(0);
        myfile2 << ", ";
        myfile2 << current_pose(1);
        myfile2 << ", ";
	myfile2 << current_pose(2);
        myfile2 << "\n";*/

		FK_D.publish(msg1);  
///


///
	end_effector_state = kinematic_state->getGlobalLinkTransform("base_footprint");
	ROS_INFO_STREAM("Translation: " << end_effector_state.translation());
/* end_effector_state initialization */
/*
if (msg->data[11] == 0){
	Eigen::Matrix3d r;
	r << 1, 0, 0,
		 0, 1, 0,
		 0, 0, 1; 

}*/
Eigen::Matrix3d r;
int jj=0;
for(jj=0; jj<4; jj++){
if (jj=0){
	
	r << 1, 0, 0,
		 0, 1, 0,
		 0, 0, 1; /* fill rotation Matrix : Here we can control the desired orientation for EE*/
}
if(jj=1){
	r << 0.7071,    0 ,  -0.7071 ,        
   		-0.7071 ,   0 ,  -0.7071  ,      
        	 0  ,  1  ,  0;         
        	 }
if(jj=2){
	r << 0.7071 ,   0 ,  0.7071 ,        
   		0.7071,    0 ,  -0.7071,         
        	 0 ,   1 ,   0   ; 
}
if(jj=3){
	r << 1     ,       0   ,         0 ,           
            0   ,   0.70711   ,  -0.70711  ,          
            0    ,  0.70711  ,    0.70711  ; 
}
  
/* Getting the desired translation for EE */
	double tx,ty,tz;
	double txc,tyc,tzc;
	double txa,tya,tza;
/* end-effector position */
/* Fill tx,ty & tz with the data from Kinect node. */ 
	//txc= msg->data[8];
	//tyc= msg->data[9];
	//tzc= msg->data[10];	
	
	
	tx= round( ( msg->data[8] * pow( 10,2 ) ) ) / pow( 10,2 );
	ty= round( ( msg->data[9] * pow( 10,2 ) ) ) / pow( 10,2 );
	tz= round( ( msg->data[10] * pow( 10,2 ) ) ) / pow( 10,2 );

	/*txa=(current_pose(0)-txc)/5;
	tya=(current_pose(1)-tyc)/5;
	tza=(current_pose(2)-tzc)/5;
int next =1;
Eigen::VectorXd joints_old(8);
	for(int i=1; i<6; i++){
		cout<<i<<endl;
		tx=ty=tz=0;
		tx= current_pose(0)-(txa*i);
		ty= current_pose(1)-(tya*i);
		tz= current_pose(2)-(tza*i);
	
		double txo,tyo,tzo;
	Eigen::Vector3d vo(txo,tyo,tzo);*/
	Eigen::Vector3d v;//(tx,ty,tz);
	v << tx, ty, tz; /* fill translation vector : */

/* EE_State filled with both translation and rotation vector/matrix */

	//if(next ==1){
		end_effector_state.translate(v);
		end_effector_state.rotate(r);
	//}
	/*else {
		end_effector_state.translate(v-vo);
		end_effector_state.rotate(r);
	}*/
/** Print end-effector pose. Remember that this is in the model frame  */

	
	ROS_INFO_STREAM("Translation: " << end_effector_state.translation());
	ROS_INFO_STREAM("Rotation: " << end_effector_state.rotation());

	

/** Inverse Kinematics. We can now solve inverse kinematics (IK) for the Cyton Gamma 1500 arm.
    To solve IK, we will need the following parameters:
	1:- The desired pose of the end-effector (by default, this is the last link in the "cyton_gamma_1500_arm" chain) -> end_effector_state that we computed in the step above.
	2:- The number of attempts to be made at solving IK: 10
	3:- The timeout for each attempt: 0.1 s */

	bool F_IK = kinematic_state->setFromIK(joint_model_group, end_effector_state, 5, 0.01);

	/* If found IK solution ... we can use for hardware */
	if (F_IK){

		kinematic_state->copyJointGroupPositions(joint_model_group, joint_values);
		
	//if(next ==1){
		CJS_D.data.push_back(msg->data[0]);
		CJS_D.data.push_back(msg->data[1]);
		CJS_D.data.push_back(msg->data[2]);
		CJS_D.data.push_back(msg->data[3]);
		CJS_D.data.push_back(msg->data[4]);
		CJS_D.data.push_back(msg->data[5]);
		CJS_D.data.push_back(msg->data[6]);
		//CJS_D.data.push_back(msg->data[7]);
	//}
	/*else{
		CJS_D.data.push_back(joints_old[0]);
		CJS_D.data.push_back(joints_old[1]);
		CJS_D.data.push_back(joints_old[2]);
		CJS_D.data.push_back(joints_old[3]);
		CJS_D.data.push_back(joints_old[4]);
		CJS_D.data.push_back(joints_old[5]);
		CJS_D.data.push_back(joints_old[6]);
		//CJS_D.data.push_back(msg->data[7]);

	}*/
		
		CJS_D.data.push_back(joint_values[0]);
		CJS_D.data.push_back(joint_values[1]);
		CJS_D.data.push_back(joint_values[2]);
		CJS_D.data.push_back(joint_values[3]);
		CJS_D.data.push_back(joint_values[4]);
		CJS_D.data.push_back(joint_values[5]);
		CJS_D.data.push_back(joint_values[6]);
		//CJS_D.data.push_back(joint_values[7]);


		

		

	

		
/*		
myfile3 << msg->data[0];
myfile3 << ", ";
myfile3 << msg->data[1];
myfile3 << ", ";
myfile3 << msg->data[2];
myfile3 << ", ";
myfile3 << msg->data[3];
myfile3 << ", ";
myfile3 << msg->data[4];
myfile3 << ", ";
myfile3 << msg->data[5];
myfile3 << ", ";
myfile3 << msg->data[6];
myfile3 << "\n";


myfile << joint_values[0];
myfile << ", ";
myfile << joint_values[1];
myfile << ", ";
myfile << joint_values[2];
myfile << ", ";
myfile << joint_values[3];
myfile << ", ";
myfile << joint_values[4];
myfile << ", ";
myfile << joint_values[5];
myfile << ", ";
myfile << joint_values[6];
myfile << "\n";


myfile1 << tx;
myfile1 << ", ";
myfile1 << ty;
myfile1 << ", ";
myfile1 << tz;
myfile1 << "\n";
*/		jj=4;

		IKCJ_D.publish(CJS_D);
	
		//sleep(1);


	}
	else
	{
		ROS_INFO("NO Inverse Kinematics Solution Found");
		ROS_INFO("Desired End-effector position is not inside WORKSPACE");
	}

	//ros::Duration(0.2).sleep(); /* Using 2.5secs sleep to make sure EE reachs is goal. */
}	

/** Get the Jacobian. We can also get the Jacobian from the :moveit_core:`RobotState`.*/
	Eigen::Vector3d reference_point_position(0.0,0.0,0.0);
	Eigen::MatrixXd jacobian;
	
	kinematic_state->getJacobian(joint_model_group, kinematic_state->getLinkModel(joint_model_group->getLinkModelNames().back()), 
	reference_point_position, jacobian);

//txo=tx; tyo=ty; tzo=tz;

//joints_old << joint_values[0], joint_values[1], joint_values[2], joint_values[3], joint_values[4],joint_values[5], joint_values[6], joint_values[7];

//next=2;
//}
/** Print Jacobian */
/*
	ROS_INFO_STREAM("Jacobian: " << jacobian);
*/
}
}
 
}


/* Main */
int main(int argc, char **argv){

    ros::init (argc, argv, "Cyton_IK");

    //ros::AsyncSpinner spinner(2);
   // spinner.start();
    ros::NodeHandle nh;
/*
myfile.open ("jsvalues.csv");
myfile1.open ("cp.csv");
myfile2.open ("m1.csv");
myfile3.open ("m2.csv");
*/
    ros::Subscriber sub = nh.subscribe ("/CJS_D", 1, callback);

    IKCJ_D = nh.advertise<std_msgs::Float32MultiArray>("/IKCJ_D", 1);

	/////////////
	FK_D = nh.advertise<geometry_msgs::PoseStamped>("/FK_D", 1);
	
 ////////////
    ros::spin();
/*
myfile.close();
 myfile1.close();
 myfile2.close();
 myfile3.close();
 */
 /* ros::shutdown();*/
  return 0;
}

