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

#include <iostream>
#include <cstdio>
#include <ctime>
using namespace std;
#define TIC tictoc(0)
#define TOC tictoc(1)

/* publisher declaration*/
//ros::Publisher gripper_joint;
ros::Publisher FSR_val;




int main(int argc, char** argv){
	int a =1;	
ros::init(argc, argv, "Cyton_GA");
ros::NodeHandle nh;
//gripper_joint = nh.advertise<std_msgs::Float64>("/gripper_position_controller/command", 1);

FSR_val = nh.advertise<geometry_msgs::PoseStamped>("/FSR_val", 1);
		

//long ti,tf;
	const int BUFFERSIZE=1024;
	int sockfd, portno, n, ret;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char inbuffer[BUFFERSIZE];	//a buffer to read messagess //
	int outbuffer;	//a buffer to send messages //
	int keepGoing=1;
	
	portno = 23;	//Port number //

	//Establish the communication link //
	sockfd = socket(AF_INET, SOCK_STREAM, 0);	// create the socket //
	if(sockfd < 0) perror("ERROR opening sfocket");
	const char* argg = "192.168.0.101";
	
	//Resolve address or IP //
	server = gethostbyname(argg);
	if(server == NULL){
		fprintf(stderr, "ERROR, no such host %s\n", argg);
		exit(0);
	}

	//Prepare address structures //
	bzero((char *) &serv_addr, sizeof(serv_addr));	//fill with zeros
	serv_addr.sin_family = AF_INET;
	bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);	//copy bytes
	serv_addr.sin_port = htons(portno);	//convert values between host and network byte order
	//connect to server //
	//fcntl(sockfd, F_SETFL, O_NONBLOCK); //make it nonblocking. Optional but remember that EAGAIN may occur if not ready
	ret = connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	if(ret < 0) perror("ERROR connecting");

		int i = 0;
		char buffer[13];
	/////
	//struct timeval t1;        //t1 é uma variável composta (estrutura) com dois campos de tipo long. Ver 
	
	//struct timeval {
            //   time_t      tv_sec;     /* seconds */
            //   suseconds_t tv_usec;    /* microseconds */
         //  };
	
	//struct timezone {
          //     int tz_minuteswest;     /* minutes west of Greenwich */
          //     int tz_dsttime;         /* type of DST correction */
         //  };


    
//////
	std::string nextCommand;
	std::string FSRup;
	std::string FSRlf;
	std::string FSRrg;
double h = 0.01;
	while(1)
	{

	   char buf[1024];
	   int numBytesRead = recv(sockfd, buf, sizeof(buf), 0);
	   if (numBytesRead > 0)
	   {
	      for (int i=0; i<numBytesRead; i++)
	      {
		 char c = buf[i];
		 if (c == 'a')
		 {
		    if (nextCommand.length() > 0)
		    {
		       printf("Next command is [%s]\n", nextCommand.c_str());
			std::istringstream iss(nextCommand);
			
			std::getline(iss, FSRup, ' ');
			std::getline(iss, FSRlf, ' ');
			std::getline(iss, FSRrg, ' ');

			int FSRU = atoi(FSRup.c_str());
			int FSRL = atoi(FSRlf.c_str());
			int FSRR = atoi(FSRrg.c_str());
/* publisher definition*/
		geometry_msgs::PoseStamped FSR_data;
		
/* EE header stamp and frame id*/
		FSR_data.header.stamp = ros::Time::now();
		FSR_data.header.frame_id = "/base1";

		FSR_data.pose.position.x=FSRU;
		FSR_data.pose.position.y=FSRL;

		FSR_val.publish(FSR_data);
	
	

	//gettimeofday(&t1, NULL);  //invoca a função para a preencher com o tempo atual!
   // printf("%ld seconds, %ld microseconds\n", t1.tv_sec, t1.tv_usec);
 
			cout << "FSRup :  " <<FSRU << endl;
			cout << "FSRlf :  " <<FSRL << endl;
			cout << "FSRrg :  " <<FSRR << endl;

		       nextCommand = "";
		    }
		 }
		 else nextCommand += c;
	      }
	   }
	   else
	   {
	      printf("Socket closed or socket error!\n");
	      break;
	   }
	}


/*Close the socket*/
close(sockfd);

return 0;


};

