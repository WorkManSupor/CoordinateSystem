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

void flipImage(const Mat &src, Mat &dst, int flipCode)
{
	flip(src,dst,flipCode);
}

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
	Mat l_dst_m;
	double l_angle_d = -180.0;								   // setting  turn angle
	Point2f center(image.cols / 2.0f, image.rows / 2.0f);	   // setting turn center point
	Mat rot_mat = getRotationMatrix2D(center, l_angle_d, 1.0); // generate rotation matrix
	warpAffine(image, l_dst_m, rot_mat, image.size());		   // process actions

	//>! printf images
	imshow("origin_image", image);	// origin image
	imshow("turn_image", l_dst_m);  // turn angle image

	//>! wait for time
	waitKey();
	return 0;
}
//=================================================================//
//                           NO_MORE                               //
//=================================================================//