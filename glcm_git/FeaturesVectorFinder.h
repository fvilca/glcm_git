#pragma once
#include "Modifier.h"
#include "Metrics.h"
class FeaturesVectorFinder{

public:
	std::vector<std::vector<double>> featuresVector;
	std::vector<Metrics*> metrics;

	void pushMetric(Metrics* newMetric){ metrics.push_back(newMetric); }
	int getNumFeatures(){ return metrics.size(); }

	///para uso de LAWSTexture
	double getFeatureOfOneImage(cv::Mat& in){

		return (*metrics[0])(in);
	}

	void getFeatureVectorReduced(std::vector<double>& features, std::vector<double>& featReduced){
		
		for(int i=0; i < features.size(); i+=2){
			featReduced.push_back((features[i]+features[i+1])/2);
		}
	}

	///para uso de GLCM
	void getFeaturesOfOneImage(cv::Mat& in, std::vector<double>& out){

		for( int i=0; i<metrics.size(); ++i){
			double temp = (*metrics[i])(in);
			out.push_back(temp);
		}
		featuresVector.push_back(out);
	}
	void getFeatureVectorAverage(std::vector<double>& features){
		
		double temp=0;
		double average=0;
		int nc = featuresVector[0].size();
		int nr = featuresVector.size();
		///std::cout<<"(nc,nr)"<<nc<<","<<nr<<"\n";

		for( int i=0; i< nc; ++i){
			for(int j=0; j<nr; ++j){
				temp += featuresVector[j][i]; 
			}
			average = temp/featuresVector.size();
			///std::cout<<"featuresVector.size(): "<<featuresVector.size()<<std::endl;
			features.push_back(average);
			temp=0;
		}
		featuresVector.clear();
	}
};
