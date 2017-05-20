#pragma once
#include "Modifier.h";
#include "DataFrameViewer.h"


class ColorReducer : public Modifier{

public:
	int factor;
public:
	ColorReducer(){}
	ColorReducer(int fact):factor(256/fact){};
	~ColorReducer(){};
	void processFrame(cv::Mat& in,cv::Mat& out){
		cv::Mat_<int> src = in;
		for(int i=0; i<in.rows; ++i){
			for(int j=0; j<in.cols; ++j){
				src(i,j)=src(i,j)/factor;
			}
		}
		out = src.clone();

		
		/*int nl = in.rows;
		int nc = in.cols * in.channels();

		uchar* data = in.ptr<uchar>(0);
		for (int i = 0; i<nc*nl; i++) {
			data[i] = data[i] / factor*factor + factor / 2;
		}
		out = in.clone();
		*/
	}

	void setFactorReduce(int newFactor){
		factor = 256/ newFactor;
	}
};