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

#include<stdio.h>
#include <math.h>

#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <sstream>

/* Namespaces */
using namespace std;
using namespace sensor_msgs;
using namespace message_filters;


typedef vector <double> record_t;
typedef vector <record_t> data_t;

//-----------------------------------------------------------------------------
// Let's overload the stream input operator to read a list of CSV fields (which a CSV record).
// Remember, a record is a list of doubles separated by commas ','.
istream& operator >> ( istream& ins, record_t& record )
  {
  // make sure that the returned record contains only the stuff we read now
  record.clear();

  // read the entire line into a string (a CSV record is terminated by a newline)
  string line;
  getline( ins, line );

  // now we'll use a stringstream to separate the fields out of the line
  stringstream ss( line );
  string field;
  while (getline( ss, field, ',' ))
    {
    // for each field we wish to convert it to a double
    // (since we require that the CSV contains nothing but floating-point values)
    stringstream fs( field );
    double f = 0.00;  // (default value is 0.0)
    fs >> f;

    // add the newly-converted field to the end of the record
    record.push_back( f );
    }

  // Now we have read a single line, converted into a list of fields, converted the fields
  // from strings to doubles, and stored the results in the argument record, so
  // we just return the argument stream as required for this kind of input overload function.
  return ins;
  }

//-----------------------------------------------------------------------------
// Let's likewise overload the stream input operator to read a list of CSV records.
// This time it is a little easier, just because we only need to worry about reading
// records, and not fields.
istream& operator >> ( istream& ins, data_t& data )
  {
  // make sure that the returned data only contains the CSV data we read here
  data.clear();

  // For every record we can read from the file, append it to our resulting data
  record_t record;
  while (ins >> record)
    {
    data.push_back( record );
    }

  // Again, return the argument stream as required for this kind of input stream overload.
  return ins;  
  }

//-----------------------------------------------------------------------------




/* Main */
int main(int argc, char **argv){

    ros::init (argc, argv, "Cyton_IK1");

    //ros::AsyncSpinner spinner(2);
   // spinner.start();
    ros::NodeHandle nh;

ofstream myfile;
 myfile.open ("CWS_000.csv");
	
 // Here is the data we want.
  data_t data;

  // Here is the file containing the data. Read it into data.
  ifstream infile( "/home/luis/catkin_ws/src/cyton_gamma_1500/pr2_moveit_tutorials/kinematics/src/cyton_000.csv" );
  infile >> data;

  // Complain if something went wrong.
  if (!infile.eof())
    {
    cout << "Fooey!\n";
    return 1;
    }

  infile.close();

  // Otherwise, list some basic information about the file.
  //cout << "Your CSV file contains " << data.size() << " records.\n";

  unsigned max_record_size = 0;
  for (unsigned n = 0; n < data.size(); n++)
    if (max_record_size < data[ n ].size())
      max_record_size = data[ n ].size();
  //cout << "The largest record has " << max_record_size << " fields.\n";

  //cout << "The second field in the fourth record contains the value " << data[ 3 ][ 1 ] << ".\n";

  
  

/** We will start by instantiating a `RobotModelLoader`_ object, which will look up
	the robot description on the ROS parameter server and construct a :moveit_core:`RobotModel` for us to use.
	.. _RobotModelLoader: http://docs.ros.org/api/moveit_ros_planning/html/classrobot__model__loader_1_1RobotModelLoader.html */

	robot_model_loader::RobotModelLoader robot_model_loader("robot_description");
	robot_model::RobotModelPtr kinematic_model = robot_model_loader.getModel();
	//ROS_INFO("Model frame: %s", kinematic_model->getModelFrame().c_str());

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
	joints << 0,0, 0, 0, 0, 0, 0, 0;
		int indx=0;
while( indx < data.size() ) {
	kinematic_state->setJointGroupPositions(joint_model_group, joints);

/* end_effector_state declared */
	Eigen::Affine3d end_effector_state;
	


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
	r << 1, 0, 0,
		 0, 1, 0,
		 0, 0, 1; /* fill rotation Matrix : Here we can control the desired orientation for EE*/

/* Getting the desired translation for EE */
	double tx,ty,tz;
	double txc,tyc,tzc;
	double txa,tya,tza;
/* end-effector position */
/* Fill tx,ty & tz with the data from Kinect node. */ 
	//txc= msg->data[8];
	//tyc= msg->data[9];
	//tzc= msg->data[10];	
	

	tx= data[indx][0];//round( ( msg->data[8] * pow( 10,2 ) ) ) / pow( 10,2 );
	ty= data[indx][1];//round( ( msg->data[9] * pow( 10,2 ) ) ) / pow( 10,2 );
	tz= data[indx][2];//round( ( msg->data[10] * pow( 10,2 ) ) ) / pow( 10,2 );

	
	Eigen::Vector3d v;//(tx,ty,tz);
	v << tx, ty, tz; /* fill translation vector : */

/* EE_State filled with both translation and rotation vector/matrix */


		end_effector_state.translate(v);
		end_effector_state.rotate(r);
	
/** Print end-effector pose. Remember that this is in the model frame  */

	
	ROS_INFO_STREAM("Translation: " << end_effector_state.translation());
	//ROS_INFO_STREAM("Rotation: " << end_effector_state.rotation());

	

/** Inverse Kinematics. We can now solve inverse kinematics (IK) for the Cyton Gamma 1500 arm.
    To solve IK, we will need the following parameters:
	1:- The desired pose of the end-effector (by default, this is the last link in the "cyton_gamma_1500_arm" chain) -> end_effector_state that we computed in the step above.
	2:- The number of attempts to be made at solving IK: 10
	3:- The timeout for each attempt: 0.1 s */

	bool F_IK = kinematic_state->setFromIK(joint_model_group, end_effector_state, 5, 0.01);

	/* If found IK solution ... we can use for hardware */
	if (F_IK){

		kinematic_state->copyJointGroupPositions(joint_model_group, joint_values);
		
cout<<"j0: "<<joint_values[0]<<" j1: "<<joint_values[1]<<" j2: "<<joint_values[2]<<" j3: "<<joint_values[3]<<" j4: "<<joint_values[4]<<" j5: "<<joint_values[5]<<" j6: "<<joint_values[6]<<endl;

	
     
      myfile << tx;
      myfile << ", ";
      myfile << ty;
      myfile << ", ";
	  myfile << tz;
      myfile << "\n";
     

		//////*gravar o ponto no ficheiro*//////
	}
	else
	{
		ROS_INFO("NIS");
		//ROS_INFO("Desired End-effector position is not inside WORKSPACE");
	}

indx++;
}

 myfile.close();

  return 0;
}

