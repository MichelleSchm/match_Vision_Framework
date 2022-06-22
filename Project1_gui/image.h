#pragma once
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

/*class image {
public:
	image();  //Default-Constructor

	int set_points();
	int delete_points();
	int open_image();

private:
	vector<Point> ListofPoints;
};*/

int openvideostream();
int setpoints();
int drawline();
int deletepoints();
float printangle();