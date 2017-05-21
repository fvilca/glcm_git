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
	GLCM glcm;
	int NUMCLASSTEXTURES;

public:
	AppGlcm(){
		NUMCLASSTEXTURES =58;				/// esto tampoco deberia dar problemas
	}
	~AppGlcm(){delete this;}
	void configDisplacements();

	void preProcessing(cv::Mat&, cv::Mat&);
	void initProcessing();
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
}

void AppGlcm::initProcessing(){

	glcm.configDisplacements(); ///X
	glcm.configFeatures();		///X

	cout
		<< nameBD << ", "
		<< nameFileResults << ", "
		<< endl;

	file.open(nameBD);
	fileResults.open(nameFileResults);
	NUMIMAGES = getNumImagesFromFile();
	cout << "NUMIMAGES :" << NUMIMAGES << endl;

	DataFrameViewer::pushHeader(
		fileResults,
		"DY",
		NUMIMAGES,
		glcm.NUMFEATURES,
		glcm.getNameFeatures()
		);
}

void AppGlcm::offLineProcessing(){

	int i=1,
		clase=0;
	file.open(nameBD);
	while(!file.eof()){
		
		std::string nameImage;
		getline(file,nameImage);
		std::cout<<"imagen: "<<i<<std::endl;
		cv::Mat src = cv::imread(nameImage,0);
		//imshow("src", src);
		cv::Mat newSrc;
		//preProcessing(src,newSrc);
		//cv::waitKey();
		
		std::string stringFeatures = "";
		glcm.execute(src,stringFeatures);
		
		//cout << " 2 +++++++++++++++++++++++++++++++++++++++" << endl;
		DataFrameViewer::push(fileResults,nameImage,stringFeatures,clase); 

		if( i%NUMCLASSTEXTURES == 0){ clase++; }
		i++;
	}
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