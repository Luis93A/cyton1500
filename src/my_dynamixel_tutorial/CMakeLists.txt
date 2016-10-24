cmake_minimum_required(VERSION 2.8.3)
project(my_dynamixel_tutorial)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package( OpenCV REQUIRED )

find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  dynamixel_controllers
  roscpp
  rospy
  std_msgs
  tf
  message_generation 
  sensor_msgs
)

find_package(PCL 1.5 REQUIRED COMPONENTS segmentation filters visualization)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})


## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)


## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## To declare and build messages, services or actions from within this
## package, follow these steps:
## * Let MSG_DEP_SET be the set of packages whose message types you use in
##   your messages/services/actions (e.g. std_msgs, actionlib_msgs, ...).
## * In the file package.xml:
##   * add a build_depend tag for "message_generation"
##   * add a build_depend and a run_depend tag for each package in MSG_DEP_SET
##   * If MSG_DEP_SET isn't empty the following dependency has been pulled in
##     but can be declared for certainty nonetheless:
##     * add a run_depend tag for "message_runtime"
## * In this file (CMakeLists.txt):
##   * add "message_generation" and every package in MSG_DEP_SET to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * add "message_runtime" and every package in MSG_DEP_SET to
##     catkin_package(CATKIN_DEPENDS ...)
##   * uncomment the add_*_files sections below as needed
##     and list every .msg/.srv/.action file to be processed
##   * uncomment the generate_messages entry below
##   * add every package in MSG_DEP_SET to generate_messages(DEPENDENCIES ...)

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder
 add_service_files(
   FILES
   SetSpeed.srv
#   Service2.srv
 )

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1.action
#   Action2.action
# )

## Generate added messages and services with any dependencies listed here
 generate_messages(
   DEPENDENCIES
   std_msgs
 )

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## To declare and build dynamic reconfigure parameters within this
## package, follow these steps:
## * In the file package.xml:
##   * add a build_depend and a run_depend tag for "dynamic_reconfigure"
## * In this file (CMakeLists.txt):
##   * add "dynamic_reconfigure" to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * uncomment the "generate_dynamic_reconfigure_options" section below
##     and list every .cfg file to be processed

## Generate dynamic reconfigure parameters in the 'cfg' folder
# generate_dynamic_reconfigure_options(
#   cfg/DynReconf1.cfg
#   cfg/DynReconf2.cfg
# )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES my_dynamixel_tutorial
  CATKIN_DEPENDS dynamixel_controllers roscpp rospy std_msgs cv_bridge image_transport sensor_msgs
  DEPENDS system_lib
 CATKIN_DEPENDS message_runtime
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS} 
)


## Declare a C++ library
# add_library(my_dynamixel_tutorial
#   src/${PROJECT_NAME}/my_dynamixel_tutorial.cpp
# )

## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
# add_dependencies(my_dynamixel_tutorial ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable
 add_executable(Cyton_FK src/Cyton_FK.cpp)
add_executable(Cyton_EE_test src/Cyton_EE_test.cpp)
add_executable(Cyton_EE_random src/Cyton_EE_random.cpp)
 add_executable(Kinect_HT src/Kinect_HT.cpp)
 add_executable(Cyton_SS src/Cyton_SS.cpp)
 add_executable(Cyton_JS src/Cyton_JS.cpp)
add_executable(Cyton_GA src/Cyton_GA.cpp)
add_executable(Cyton_FSM src/Cyton_FSM.cpp)
add_executable(Cyton_home src/Cyton_home.cpp)
add_executable(Kinect_Cyton_TF src/Kinect_Cyton_TF.cpp)
 add_executable(cyton_SV src/cyton_SV.cpp)
add_executable(try src/try.cpp)
add_executable(testews src/testews.cpp)
add_executable(try1 src/try1.cpp)
add_executable(try2 src/try2.cpp)
 add_executable(Cyton_FC_open src/Cyton_FC_open.cpp)
add_executable(Cyton_FC_close src/Cyton_FC_close.cpp)
add_executable(Cyton_FC_control src/Cyton_FC_control.cpp)

add_executable(objdetred src/objdetred.cpp)
add_executable(objdetblue src/objdetblue.cpp)
add_executable(objdetgreen src/objdetgreen.cpp)
#add_executable(Kinect_Cyton_TF src/Kinect_Cyton_TF.cpp)
## Add cmake target dependencies of the executable
## same as for the library above
# add_dependencies(my_dynamixel_tutorial_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
target_link_libraries(Cyton_FK ${catkin_LIBRARIES})
target_link_libraries(Cyton_EE_test ${catkin_LIBRARIES})
target_link_libraries(Cyton_EE_random ${catkin_LIBRARIES})
target_link_libraries(Kinect_HT ${catkin_LIBRARIES})
target_link_libraries(Cyton_SS ${catkin_LIBRARIES})
target_link_libraries(Cyton_JS ${catkin_LIBRARIES})
target_link_libraries(Cyton_GA ${catkin_LIBRARIES})
target_link_libraries(Cyton_FSM ${catkin_LIBRARIES})
target_link_libraries(Cyton_home ${catkin_LIBRARIES})
target_link_libraries(cyton_SV ${catkin_LIBRARIES})
target_link_libraries(try ${catkin_LIBRARIES})
target_link_libraries(testews ${catkin_LIBRARIES})
target_link_libraries(try1 ${catkin_LIBRARIES})
target_link_libraries(try2 ${catkin_LIBRARIES})
target_link_libraries(Cyton_FC_open ${catkin_LIBRARIES})
target_link_libraries(Cyton_FC_close ${catkin_LIBRARIES})
target_link_libraries(Cyton_FC_control ${catkin_LIBRARIES})
target_link_libraries(objdetred ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} ${PCL_LIBRARIES}) #########
target_link_libraries(objdetblue ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} ${PCL_LIBRARIES}) #########
target_link_libraries(objdetgreen ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} ${PCL_LIBRARIES}) #########

target_link_libraries(Kinect_Cyton_TF ${catkin_LIBRARIES}  ${PCL_LIBRARIES})
#target_link_libraries(Kinect_Cyton_TF ${catkin_LIBRARIES})
add_dependencies(Cyton_SS my_dynamixel_tutorial_gencpp)



#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS my_dynamixel_tutorial my_dynamixel_tutorial_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_my_dynamixel_tutorial.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
