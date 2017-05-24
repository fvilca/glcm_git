#pragma once

//#include "DataFrameViewer.h"
#include "GLCMDescriptor.h"
#include "App.h"
/*
nuestro aplicativo coge una BD de imagenes y le aplica el descriptor en este caso GLCM
generando un nuevo archivo agregando el resultado de cada caracteristica
*/

class AppGlcm: public App{
	
private:
	GLCM *glcm;
	int color;
	int step;
	int angle;
	int NUMCLASSTEXTURES;

public:
	AppGlcm(){
		NUMCLASSTEXTURES = 0;				/// esto tampoco deberia dar problemas
	}
	~AppGlcm(){delete this;}

	void setNumClass(int num) { NUMCLASSTEXTURES = num; }
	///void configDisplacements();

	void preProcessing(cv::Mat&, cv::Mat&);
	void initProcessing(int,int, int);
	void offLineProcessing();
	void onLineProcessing();
	void endProcessing();
};

/*
Definimos parametros
de preprocesamiento antes de aplicar el descriptor
*/

void AppGlcm::preProcessing(cv::Mat& in,cv::Mat& out){
	
	//cv::pyrUp(in,out);
	///cv::erode(src,src,cv::Mat(),cv::Point(-1,-1),3);
	//cv::dilate(src,src,cv::Mat(),cv::Point(-1,-1),3);
	///cv::Sobel(src,src,CV_8U,1,0,3,0.4,128);//cv::Sobel(image,sobelY,CV_8U,0,1,3,0.4,128);

	int nl= in.rows; 
	int nc= in.cols * in.channels();

	uchar* data= in.ptr<uchar>(0);
	for (int i=0; i<nc*nl; i++) {
		data[i]= data[i]/32*32 + 32/2;
	}
	out = in.clone();
	imshow("preProcessing ", out);
	waitKey(0);
}

void AppGlcm::initProcessing(int step, int angle, int num_colors) {

	this->step = step;
	this->angle = angle;
	this->color = num_colors;

	cout << "initProcessing\n";
	glcm = new GLCM;
	
	glcm->configDisplacements(step,angle); ///X
	glcm->configFeatures();		///X
	glcm->red.setFactorReduce(num_colors);
	cout
		<< nameBD << ", "
		<< nameFileResults << ", "
		<< endl;

	
	NUMIMAGES = getNumImagesFromFile();
	cout << "NUMIMAGES :" << NUMIMAGES << endl;

	DataFrameViewer::pushHeader(
		fileResults,
		"DY",
		NUMIMAGES,
		glcm->NUMFEATURES,
		glcm->getNameFeatures()
		);
}

void AppGlcm::offLineProcessing(){
	cout << "offLineProcessing\n";
	
	int i = 0,
		clase = 0;

	file.open(nameBD);
	fileResults.open(nameFileResults, fstream::app);

	while (!file.eof()) {
		std::string nameImage;
		getline(file, nameImage);
		cv::Mat src = cv::imread(nameImage, 0);
		std::string stringFeatures = "";
			
		glcm->execute(src, stringFeatures);
		DataFrameViewer::push(color,step,angle,fileResults, nameImage, stringFeatures, clase);

		if (i%NUMCLASSTEXTURES == 0) { clase++; }
		i++;
	}
	file.close();
	fileResults.close();
}

void AppGlcm::onLineProcessing(){
	
}

void AppGlcm::endProcessing(){
	file.close();
	fileResults.close();
	cv::waitKey();
}

AppGlcm* getApplication(){
	return new AppGlcm();
}

/*DataFrameViewer::pushHeader(	nameFileResults,"DY",NUMIMAGES,	glcm.NUMFEATURES,getNameFeatures(glcm.featureFinder.metrics)	);*/
//DataFrameViewer::displayVectorByFile( featuresForAllDisplacements,nameFileResults, nameImage, clase); ///este nombre no es para todo solo es para uno y deberia haber uno aqui y otro fuera del While
		//cv::imshow(" ",src);
		//cv::waitKey();