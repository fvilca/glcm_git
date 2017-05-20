#pragma once
#include "Modifier.h";
#include "Displacement.h"


class KernelFinder : public Modifier{

private:
	Displacement displacement;

public:

	KernelFinder (){}
	KernelFinder (Displacement d):displacement(d){}
	void setDisplacement(Displacement d){ displacement = d;}

	void processFrame(cv::Mat& src,cv::Mat& dst){

		dst=cv::Mat::zeros(8,8,CV_8UC1);

		cv::Mat_<int> mat = src;
		cv::Mat_<int> kernel = dst;
		for(int i=0; i<src.rows; ++i){
			for(int j=0; j<src.cols; ++j){

				if(i+displacement.angle < src.rows && j+displacement.step < src.cols){	
					if(i+displacement.angle > 0 && j+displacement.step > 0){
						int a = mat(i,j);
						int b = mat(i+displacement.angle, j+displacement.step);
						kernel(a,b)++;
					}
				}
			}
			dst= kernel.clone();
		}
	}

};