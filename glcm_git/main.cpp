#include <iostream>
#include <opencv2\opencv.hpp>
using namespace std;
using namespace cv;

#include "App.h"
#include "AppGlcm.h"

int main() {

	App* app = getApplication();
	app->setNameBD("in.data");
	app->setNameResults("out.data");
	app->initProcessing();
	app->offLineProcessing();
	app->onLineProcessing();
	app->endProcessing();


	/*Mat mat = imread("img.jpg");
	imshow("xd", mat);
	waitKey();*/

	return 1;
}