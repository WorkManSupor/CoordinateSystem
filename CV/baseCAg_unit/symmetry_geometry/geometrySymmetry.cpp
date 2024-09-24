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
	//>! check argc input
	// if (argc != 2)
	// {
	// 	cout << "Usage: ./FlipImage <Image Path>" << endl;
	// 	return -1;
	// }

	//>! load source jpg
	Mat image = imread("base.jpg");
	if (!image.data)
	{
		cout << "image load error !" << endl;
		return -1;
	}

	//>! turn center
	Mat l_dst_m;
	double l_angle_d = 90.0;								   // setting  turn angle
	Point2f center(image.cols / 2.0f, image.rows / 2.0f);	   // setting turn center point
	Mat rot_mat = getRotationMatrix2D(center, l_angle_d, 1.0); // generate rotation matrix
	warpAffine(image, l_dst_m, rot_mat, image.size());		   // process actions

	//>! geometry turn image
	Mat flipped_horizontal, flipped_vertical, flipped_center;
	flipImage(image, flipped_horizontal, 1);
	flipImage(image, flipped_vertical, 0);
	flipImage(image, flipped_center, -1);

	//>! printf images
	imshow("origin_image", image);			          	// origin image
	imshow("Flipped_Horizontally", flipped_horizontal); // horizontally image
	imshow("Flipped_Vertically", flipped_vertical);		// vertically image
	imshow("flipped_center", flipped_center);			// center image

	//>! wait for time
	waitKey();
	return 0;
}
//=================================================================//
//                           NO_MORE                               //
//=================================================================//