#pragma once
#include "DataFrameViewer.h"
#include "Modifier.h"
#include "ColorReducer.h"
#include "KernelFinder.h"
#include "FeaturesVectorFinder.h"
#include "Displacement.h"
#include "MatrixNormalizer.h"
#include <fstream>
#include <sstream>

class GLCM{

public:

	Displacements displacements;
	int NUMDISPLACEMENTS;
	int NUMFEATURES;
	ColorReducer red;
	FeaturesVectorFinder featureFinder;

	bool isFeaturesEnabled;
	bool isDisplacementsEnabled;

	std::vector<double> featuresForAllDisplacements;

public:
	GLCM(){ 
		red.setFactorReduce(8);
	}
	bool enabledGLCM();
	std::string getNameFeatures();
	void configDisplacements();
	void configFeatures();
	bool execute(cv::Mat& src, std::string& str);
	std::string featuresToString(void);
};

std::string GLCM::getNameFeatures(){
	std::string names="";
	for( int i=0; i<featureFinder.metrics.size(); ++i){
		names.append((*featureFinder.metrics[i]).label());
		names.append(";");
	}
	names.pop_back();
	return names;
}

std::string GLCM::featuresToString(){
	
	std::string str;
	
	for( int i=0; i<featuresForAllDisplacements.size(); ++i){
		double value = featuresForAllDisplacements[i];
		std::ostringstream strs;
		strs << value<<";";
		std::string temp = strs.str();
		str.append(temp);
	}	
	return str;
}

bool GLCM::enabledGLCM(){

	if(isDisplacementsEnabled && isFeaturesEnabled ){
		std::cout<<"Configuracion Incompleta, no se puede Ejecutar GLCM\n";
		if (displacements.getNumDisplacements() && featureFinder.getNumFeatures() )
			std::cout<<"Displacements o Features sin definir\n";
		return false;	
	}
	return true;
}

void GLCM::configDisplacements(){ ///esto no debe estar aqui se supone que esto es cerrado

	displacements.push(Displacement(20,10));
	displacements.push(Displacement(10,-20));
	displacements.push(Displacement(20,20));
	displacements.push(Displacement(20,-20));	
	displacements.push( Displacement(-10,-10));

	NUMDISPLACEMENTS = displacements.getNumDisplacements();
	isDisplacementsEnabled = true;
	cout << "configDisplacements " << endl;
}

bool GLCM::execute(cv::Mat& src , std::string& strFeatures){


	///if ( !enabledGLCM() ) {		return false;}
	NUMFEATURES =  featureFinder.getNumFeatures();
	int countDisplacements=0;
	cv::Mat imgReduced;
	red.processFrame(src,imgReduced);
	///imshow("out reduced", imgReduced);
	///waitKey();
	DataFrameViewer::displayByFile(imgReduced,"reducido.txt");
	std::cout << "x"<<endl;

	while(countDisplacements < NUMDISPLACEMENTS){
		
		cv::Mat kernel;
		KernelFinder kernelFinder(displacements.vector[countDisplacements]);
		
		kernelFinder.processFrame(imgReduced, kernel);
		DataFrameViewer::displayByFile(kernel,"MatrizCoOcurrencia.txt");
			
		cv::Mat kernelNormalized;
		MatrixNormalizer matNormalizer;
		matNormalizer.processFrame(kernel,kernelNormalized);
		DataFrameViewer::displayByFile(kernelNormalized,"MatrizCoOcurrenciaNorm.txt");
		
		std::vector<double> featuresForOneDisplacement;
		featureFinder.getFeaturesOfOneImage(kernelNormalized,featuresForOneDisplacement);
		featuresForOneDisplacement.clear();
		countDisplacements++;
	}
	featureFinder.getFeatureVectorAverage(featuresForAllDisplacements);
	strFeatures = featuresToString();
	featuresForAllDisplacements.clear();
	return true;
}


void GLCM::configFeatures(){

	
	featureFinder.pushMetric(new Energy);
	featureFinder.pushMetric(new Maximun);
	featureFinder.pushMetric(new Disimilarity);
	featureFinder.pushMetric(new Contrast);
	featureFinder.pushMetric(new LocalHomogeneity);
	featureFinder.pushMetric(new Correlation);
	featureFinder.pushMetric(new Entropy);
	featureFinder.pushMetric(new Mean);

	NUMFEATURES =  featureFinder.getNumFeatures();
	isFeaturesEnabled = true;
	cout << "configFeatures " << endl;
}

