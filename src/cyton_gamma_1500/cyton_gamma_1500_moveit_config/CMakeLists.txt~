cmake_minimum_required(VERSION 2.8.3)
project(cyton_gamma_1500_moveit_config)

find_package(cmake_modules REQUIRED)
find_package(catkin REQUIRED COMPONENTS
		roscpp
		moveit_ros_move_group
		moveit_planners_ompl
		moveit_ros_visualization
		joint_state_publisher
		robot_state_publisher
		xacro
		cyton_gamma_1500_description
	
	
		descartes_core
		descartes_moveit
		descartes_trajectory
		descartes_planner
		trajectory_msgs
		)

find_package(Eigen REQUIRED)

include_directories(SYSTEM ${Boost_INCLUDE_DIR} ${EIGEN_INCLUDE_DIRS} ${catkin_INCLUDE_DIRS})

catkin_package()

install(DIRECTORY launch DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

install(DIRECTORY config DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})


