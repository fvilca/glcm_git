#pragma once
#include "Modifier.h";


class MatrixNormalizer : public Modifier{

public:
	void processFrame(cv::Mat& src,cv::Mat& dst){
		
		cv::Mat_<int> in = src;
		//dst.create(src.rows, src.cols,cv::DataType<double>::type);
		cv::Mat_<double> out;
		out.create(src.rows, src.cols);
		///out = dst;

		double normalizationFactor= 0.0;

		for(int i=0; i<src.rows; ++i){
			for(int j=0; j<src.cols; ++j){
				normalizationFactor += in(i,j);
			}
		}

		for(int i=0; i<src.rows; ++i){
			for(int j=0; j<src.cols; ++j){
				out(i,j) = round((double)in(i,j)/normalizationFactor);
			}
		}    

		dst = out.clone();
		//double maxValue;
		//double minValue;

		//cv::minMaxLoc(src,&minValue,&maxValue);
		///std::cout<<minValue <<" "<<maxValue<<std::endl;
		//cv::normalize(src, dst, 0, 1, cv::NORM_MINMAX, CV_32S );

	}
	double round(double d,unsigned int p=5){

		unsigned int fac=pow(10,double(p));
		double facinv=1.0/static_cast<double>(fac);
		double x=static_cast<unsigned int>(d*fac)*facinv;
		return x;
	}
};