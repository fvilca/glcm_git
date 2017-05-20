#pragma once

#include <fstream>
#include <cmath>


class App{

protected:
	std::string nameBD;
	std::ifstream file;
	std::string nameFileResults;
	std::ofstream fileResults;
	int NUMIMAGES;
	
public:
	App(){		
		NUMIMAGES = 0;
	}
	virtual ~App(void){}
	int getNumImagesFromFile(){

		int numLines = 0;

		while(!file.eof()){
			getline(file,std::string());
			numLines++;
		}
		file.close();

		std::cout<<"#images: "<<numLines<<std::endl;
		return numLines;
	}
	void setNameBD(std::string name) { 
		nameBD = name; 
		cout<<"setNameBD "<<endl;
	}
	void setNameResults(std::string name){ 
		nameFileResults = name;
		cout << "setNameResults " << endl;
	}
	
	virtual void preProcessing(cv::Mat&, cv::Mat&)=0;
	virtual void initProcessing()=0;
	virtual void offLineProcessing()=0;
	virtual void onLineProcessing()=0;
	virtual void endProcessing()=0;
};
