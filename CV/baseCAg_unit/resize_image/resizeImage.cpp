//=================================================================//
//                          core algorithm                         //
//    opencv base function: load image(*jpg)                       //
//    description         : only funciton unit                     //
//=================================================================//
// sys, base hpp
//=================================================================//
#include "iostream"

//=================================================================//
// lib import
//=================================================================//
#include "opencv2/opencv.hpp"

//=================================================================//
using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
	//>! load source jpg
	Mat image = imread("base.jpg");
	if (!image.data)
	{
		cout << "image load error !" << endl;
		return -1;
	}

	//>! turn center
	Mat l_outPic_m, l_outIma_m, l_outdbIma_m;
	resize(image, l_outPic_m, Size(320, 680), 0, 0);
	resize(image, l_outIma_m, Size(0, 0), 0.5, 0.5);
	resize(image, l_outdbIma_m, Size(0, 0), 2, 2);

	//>! printf images
	imshow("origin_image", image);	// origin image
	imshow("cur_image",l_outPic_m);
	imshow("short_image", l_outIma_m);  // turn angle image
	imshow("double_image",l_outdbIma_m);

	//>! wait for time
	waitKey();
	return 0;
}
//=================================================================//
//                           NO_MORE                               //
//=================================================================//