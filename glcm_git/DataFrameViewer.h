#pragma once
#include <opencv2\opencv.hpp>
#include <fstream>

class DataFrameViewer{
	
	///std::ofstream fout;

public:

	DataFrameViewer(void){
		///fout.open("resultados.txt");
	}

	static void  pushHeader(std::ofstream& toFile, std::string type, int numImages, int numFeat, std::string nameFeatures){
		
		toFile<<type<<"\n"
			  <<numImages<<"\n"
			  <<numFeat<<"\n"
			  <<nameFeatures<<"\n";
	}
	static void displayByFile(cv::Mat& src, std::string nameFile){

		std::ofstream toFile(nameFile, std::ios::app);

		cv::Mat_<double> _src = src;
		for(int i=0; i<_src.rows; ++i){
			for(int j=0; j<_src.cols; ++j){
				toFile<<(double)_src(i,j)<<"\t\t";
			}
				toFile<<std::endl;
		}
		toFile<<std::endl;
		toFile.close();
		///system(nameFile);
	}

	static void displayVectorByFile(std::vector<double> metrics, std::string nameFile, std::string imgFile,int clase){

		std::ofstream toFile(nameFile,std::ios::app);

		toFile<<imgFile<<";";
		std::vector<double>::iterator it;
		for(it = metrics.begin(); it != metrics.end(); ++it){
			toFile<<*it<<";";
		}
		toFile<<clase;
		toFile<<std::endl;
		
///		toFile.close();
		///std::cout<<"Archivo generado satisfactoriamente \n";
	}


	static void displayByConsole(cv::Mat& src){

		cv::Mat_<double> _src = src;
		for(int i=0; i<_src.rows; ++i){
			for(int j=0; j<_src.cols; ++j){
				std::cout<<(double)_src(i,j)<<"\t";
			}
				std::cout<<std::endl;
		}
		std::cout<<std::endl;
	}

	

	static void displayByConsoleInt(cv::Mat& src){

		cv::Mat_<int> _src = src;
		for(int i=0; i<_src.rows; ++i){
			for(int j=0; j<_src.cols; ++j){
				std::cout<<(int)_src(i,j)<<"\t";
			}
				std::cout<<std::endl;
		}
		std::cout<<std::endl;
	}

	static  void displayVectorbyConsole(std::string s, std::vector<double> v){

		std::vector<double>::iterator it;
		std::cout<<s<<":\n";
		for(it = v.begin(); it!= v.end(); ++it){
			std::cout<<*it<<"\n";
		}
		std::cout<<std::endl;
	}

	static void push(int color, int step, int angle,std::ofstream& toFile, std::string imgFile,std::string strFeatures,int clase){

		toFile << color << "; "
			<< step << "; "
			<< angle << "; "
			<< imgFile << ";"
			<<strFeatures
			<<clase
			<<std::endl;
	}

};
