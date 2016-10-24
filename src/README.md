# Cyton-gamma-1500 manipulator, under ROS indigo , ubuntu 14.04 
Author : Luís Almeida, lmalmeida@ua.pt
 

 roslaunch my_dynamixel_tutorial controller_manager.launch - find Cyton servos
 roslaunch my_dynamixel_tutorial start_tilt_controller.launch - start the servos controller_manager

 roslaunch openni_launch openni.launch - launch openni for Kinect
 rosrun openni_tracker openni_tracker - launch the tracker, to detect the hand coordinates
 optional (rviz for skeleton vizualization) - rosrun rviz 
 rosrun my_dynamixel_tutorial Kinect_HT - node responsible for the hand coordinates and the frame transformation
 rosrun my_dynamixel_tutorial objdetred - node responsible for the red cube detection 
 
 rosrun my_dynamixel_tutorial cyton_EE_test - run the node that contains the desired EE position
 rosrun my_dynamixel_tutorial cyton_JS -  run the node that contains all the information about the servos

 roslaunch pr2_moveit_tutorials kinematic_model_tutorial - launch the inverse kinematic solver

 rosrun my_dynamixel_tutorial Cyton_SV - run the node responsible for the synchronization and the foward kinematics

 rosrun my_dynamixel_tutorial Cyton_GA - node that receives the FSR feedback
 rosrun my_dynamixel_tutorial try - node that manages the task states
 rosrun my_dynamixel_tutorial try1 - node that controls the gripper actions based on the force feedback

This aplication allows someone with the proper hardware and software to execute a object transfer task with a robotic arm.
 



