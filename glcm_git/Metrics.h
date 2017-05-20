#pragma once
#include <opencv2\opencv.hpp>
#include <stdlib.h>
#include <math.h>


class Metrics{
	protected:
		double result;
	public:
		Metrics():result(0.0){}
		virtual double operator()(const cv::Mat& in)=0;
		virtual std::string label()=0;
};


class Energy : public Metrics{

public:
	double  operator()(const cv::Mat& in){	
		cv::Mat_<double> mat = in;
		double energy=0;
		for(int i=0; i<mat.rows; ++i){
			for(int j=0; j<mat.cols; ++j){
				energy += mat(i,j)*mat(i,j);
			}
		}
		return energy;
	}
	std::string label(){ return "energy";}

};


class Entropy : public Metrics{
public:
	double  operator()(const cv::Mat& in){
		cv::Mat_<double > mat = in;
		result = 1;
		for(int i=0; i<mat.rows; ++i){
			for(int j=0; j<mat.cols; ++j){
				if(mat(i,j)>0.0)
					///result -= result*std::log((double )mat(i,j));
					//result += mat(i,j) * std::log((double )mat(i,j));
				   result -= mat(i,j) * std::log((double)mat(i,j)); 
			}
		}
		return result;
		//return (result * (-1)) / std::log((double )(256*256));
	}
	std::string label(){ return "entropy";}
};
        

class Maximun: public Metrics{///cv::minMaxIdx(nuevo,&min,&max);

public:

	double  operator()(const cv::Mat& in){

		double max=0;
		cv::Mat_<double > mat = in;
		for(int i=0; i<mat.rows; ++i){
			for(int j=0; j<mat.cols; ++j){
				max = std::max<double>(max,mat(i,j));
			}
		}
		return max;
	}
	std::string label(){ return "maximun";}
};


class Contrast: public Metrics{

public:
	double  operator()(const cv::Mat& in){
		cv::Mat_<double> mat = in;
		double contrast=0;
		for(int i=0; i<mat.rows; ++i){
			for(int j=0; j<mat.cols; ++j){
				contrast += (i - j) * (i - j) * mat(i,j);   
			}
		}
		return contrast;
	}
	std::string label(){ return "contrast";}
};

class Correlation: public Metrics{

public:
	double operator()(const cv::Mat& in){

		cv::Mat_<double> mat = in;
		double yMean=0;
		double xMean=0;
		double yVariance=0;
		double xVariance=0;
		double yStdDev=0;
		double xStdDev=0;
		double correlation=0;
		for(int i=0; i<mat.rows; ++i){
			for(int j=0; j<mat.cols; ++j){
				xMean += j * mat(i,j);
				yMean += i * mat(i,j);
			}
		}

		for(int i=0; i<mat.rows; ++i){
			for(int j=0; j<mat.cols; ++j){
				xVariance += (j-xMean)*(j-xMean) * mat(i,j);
				yVariance += (i-yMean)*(i-yMean) * mat(i,j);
			}
		}

		xStdDev= sqrt(xVariance);
		yStdDev= sqrt(yVariance);

		if(xStdDev !=0 && yStdDev !=0 )  {

			for(int i=0; i<mat.rows; ++i){
				for(int j=0; j<mat.cols; ++j){
					correlation += (j-xMean)*(j-xMean)*mat(i,j) / (xStdDev * yStdDev);

				}
			}
			///std::cout<<"corr: "<<result<<std::endl;
		}///end if
		return correlation;
	}
	std::string label(){ return "correlation";}
};

class Mean: public Metrics{

public:
	double  operator()(const cv::Mat& in){	
		cv::Mat_<double> mat = in;
		double mean=0;
		for(int i=0; i<mat.rows; ++i){
			for(int j=0; j<mat.cols; ++j){
				mean += mat(i,j);
			}
		}
		return mean/(mat.rows*mat.cols);
	}
	std::string label(){ return "mean";}
};
//inversedifmoment
class LocalHomogeneity: public Metrics{
	
public:
	double  operator()(const cv::Mat& in){	
		cv::Mat_<double> mat = in;
		double homogeneity=0;
		for(int i=0; i<mat.rows; ++i){
			for(int j=0; j<mat.cols; ++j){
				homogeneity += mat(i,j)/(1+(i-j)*(i-j));
			}
		}
		return /*homogeneity;*/homogeneity/(mat.rows*mat.cols);
	}
	std::string label(){ return "homogeneity";}
};

class Disimilarity: public Metrics{
	
public:
	double  operator()(const cv::Mat& in){	
		double disimilarity=0;
		cv::Mat_<double> mat = in;
		for(int i=0; i<mat.rows; ++i){
			for(int j=0; j<mat.cols; ++j){
				disimilarity += mat(i,j)*std::abs(i-j);
			}
		}
		return /*disimilarity;*/disimilarity/(mat.rows*mat.cols);
	}
	std::string label(){ return "disimilarity";}
};
