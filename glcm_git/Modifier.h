#pragma once
#include <opencv2\opencv.hpp>
#include <fstream>
#include <cmath>


class Modifier
{
protected:
	cv::Mat frame;
	
public:
	//virtual ~Modifier(void){}
	virtual void processFrame(cv::Mat& in, cv::Mat& out)/*const*/=0;
};