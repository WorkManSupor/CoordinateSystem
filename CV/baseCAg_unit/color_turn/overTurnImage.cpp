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

    //>! over turn image
	Mat image_inverted;
	bitwise_not(image,image_inverted);

    //>! output image
	imwrite("overTurnImageOutput.png", image_inverted);
	
	//>! printf over turn image
	namedWindow("overTurnImageOutput", 1);
	imshow("overTurnImageOutput", image_inverted);
	
	//>! wait for time
	waitKey();
	return 0;
}
//=================================================================//
//                           NO_MORE                               //
//=================================================================//