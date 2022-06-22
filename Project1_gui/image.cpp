#include <opencv2/core/core.hpp> 
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>
#include "image.h"


using namespace cv;
using namespace std;
VideoCapture cap(0);
Mat img;
Point pointglobal;
vector<Point> pointList;
bool lineon = false;

int openvideostream() {
	while (true) {
		cap.read(img);
		namedWindow("Video", 1);
		imshow("Video", img);
		waitKey(1);
	}

	return 0;
}

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN) {
		cout << "Left button of the mouse is clicked - position (" << x << "," << y << ")" << endl;
		pointglobal.x = x;
		pointglobal.y = y;
		pointList.push_back(pointglobal);
		circle(img, pointglobal, 2, Scalar(0, 0, 255), FILLED, LINE_8);


	}
}

int setpoints() {
	setMouseCallback("Video", CallBackFunc, NULL);
	while (true) {
		cap.read(img);
		for (int i = 0; i < pointList.size(); i++) {
			circle(img, pointList[i], 2, Scalar(0, 0, 255), FILLED, LINE_8);
		}
		namedWindow("Video", 1);
		imshow("Video", img);
		waitKey(1);
	}
	return 0;

}
int drawline() {
	if (pointList.size() == 2) {
		line(img, pointList[0], pointList[1], Scalar(255, 0, 255), 1, 8);
		lineon = true;
	}
	while (true) {
		cap.read(img);
		for (int i = 0; i < pointList.size(); i++) {
			circle(img, pointList[i], 2, Scalar(0, 0, 255), FILLED, LINE_8);
		}
		if (lineon == true) {
			line(img, pointList[0], pointList[1], Scalar(255, 0, 255), 1, 8);
		}
		namedWindow("Video", 1);
		imshow("Video", img);
		waitKey(1);
	}

	return 0;
}

int deletepoints() {
	lineon = false;
	pointList.clear();
	return 0;
}

float getAngle(Point Point1, Point Point2) {
	float deltax = Point1.x - Point2.x;
	float deltay = Point1.y - Point2.y;
	float tan = deltay / deltax;
	float alpha = atan(tan);
	return alpha;
}

float printangle() {
	if (pointList.size() == 2) {
		float alpha = getAngle(pointList[0], pointList[1]);
		float winkel = alpha * 180 / 3.1415;
		winkel = (int)(winkel * 100);
		winkel = winkel / 100;
		return winkel;
	}
	return 0;
}