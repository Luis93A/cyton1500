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
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;


#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

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
// Now to put it all to use.
int main()
  {
  // Here is the data we want.
  data_t data;

  // Here is the file containing the data. Read it into data.
  ifstream infile( "/home/luis/catkin_ws/src/cyton_gamma_1500/pr2_moveit_tutorials/kinematics/src/t.csv" );
  infile >> data;

  // Complain if something went wrong.
  if (!infile.eof())
    {
    cout << "Fooey!\n";
    return 1;
    }

  infile.close();

  // Otherwise, list some basic information about the file.
  cout << "Your CSV file contains " << data.size() << " records.\n";

  unsigned max_record_size = 0;
  for (unsigned n = 0; n < data.size(); n++)
    if (max_record_size < data[ n ].size())
      max_record_size = data[ n ].size();
  cout << "The largest record has " << max_record_size << " fields.\n";

  cout << "The second field in the fourth record contains the value " << data[ 2 ][ 0 ] << ".\n";

  cout << "Good bye!\n";
  return 0;
  }

	


/*
int main(int argc, char **argv){

    ros::init (argc, argv, "Cyton_IK");

    //ros::AsyncSpinner spinner(2);
   // spinner.start();
    ros::NodeHandle nh;

int j=0;
double dat[3][3];

double num1, num2, num3;

ifstream indata;
indata.open( "/home/luis/catkin_ws/src/cyton_gamma_1500/pr2_moveit_tutorials/kinematics/src/t.csv");

if(!indata) { cout << "Error: file could not be opened" << endl; }
indata >> num1 >> num2 >> num3 ;

	dat[j][1] =num1;
	dat[j][2] =num2;	
	dat[j][3] =num3;
cout << "The next number is " << num1 << num2 << num3<<endl;
/*
while (!indata.eof()) {// keep reading until end-of-file
	j++;
	dat[j][1] =num1;
	dat[j][2] =num2;	
	dat[j][3] =num3;

}*/
/*
vector <vector <string> > data;
  ifstream infile( "/home/luis/catkin_ws/src/cyton_gamma_1500/pr2_moveit_tutorials/kinematics/src/t.csv" );

  while (infile)
  {
    string s;
    if (!getline( infile, s )) break;

    istringstream ss( s );
    vector <string> record;

    while (ss)
    {
      string s;
      if (!getline( ss, s, ',' )) break;
      record.push_back( s );
    }

    data.push_back( record );
  }
  if (!infile.eof())
  {
    cerr << "Fooey!\n";
  }
*/

/*
*/

/*
ifstream myReadFile;
 myReadFile.open("/home/luis/catkin_ws/src/cyton_gamma_1500/pr2_moveit_tutorials/kinematics/src/t.csv");
string output;

 if (myReadFile.is_open()) {
 while (!myReadFile.eof()) {
	

    myReadFile >> output;
	
	//dat[j][1]
//    cout<<output<<endl;
	  cout << "First 5 chars are [" << output.substr(0,6) << "]" << endl;
//cout << "->" << dat[1][1] << endl;
}}


*/



//}
