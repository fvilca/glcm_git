#include <iostream>
#include <opencv2\opencv.hpp>
using namespace std;
using namespace cv;

#include "App.h"
#include "AppGlcm.h"

int main() {

	AppGlcm* app = getApplication();
	app->setNumClass(2);
	app->setNameBD("in.data");
	app->setNameResults("out.csv");

		int color_fin = 12;
		int step_fin = 16;
		int angle_fin = 16;

		for (int c = 4; c <= color_fin; c++) {
			cout << "***************************************** " << c << endl;
			for (int i = 2; i < step_fin; i++)
			{
				for (int j = 2; j < angle_fin; j++)
				{
					app->initProcessing(i,j,c);
					app->offLineProcessing();
				}
			}

		}
	
	app->onLineProcessing();
	app->endProcessing();

	///system("out.data");

	/*Mat mat = imread("img.jpg");
	imshow("xd", mat);
	waitKey();*/

	return 1;
}