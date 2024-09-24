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
	if (image.empty())
	{
		cout << "image load error !" << endl;
		return -1;
	}

    //>! output image
	imwrite("loadImageOutput.png", image);
	
	//>! printf over turn image
	namedWindow("loadImageOutput", 1);
	imshow("loadImageOutput", image);
	
	//>! wait for time
	waitKey();
	return 0;
}
//=================================================================//
//                           NO_MORE                               //
//=================================================================//


