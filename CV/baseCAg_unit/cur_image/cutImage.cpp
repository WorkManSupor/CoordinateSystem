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
	Mat gridImg;
	unsigned int l_starX_i = 100;
	unsigned int l_starY_i = 100;
	unsigned int l_width_i = 200;
	unsigned int l_height_i = 150;

	//>! cut image
	unsigned int l_rows = 3;				   // grid rows
	unsigned int l_cols = 2;				   // grid cols
	unsigned int l_grid_w = image.cols / l_cols; // each grid width
	unsigned int l_grid_h = image.rows / l_rows; // each grid hight
	unsigned int l_n = 0;
	for (unsigned int l_indI = 0; l_indI < l_rows; l_indI++)
	{
		for (unsigned int l_indJ = 0; l_indJ < l_cols; l_indJ++)
		{
			//>! cacluation current grid left update
			unsigned int l_srcX_i = l_indJ * l_grid_w;
			unsigned int l_srcY_i = l_indI * l_grid_h;

			//>! cut current grid net
			Rect roi(l_srcX_i, l_srcY_i, l_grid_w, l_grid_h);
			gridImg = image(roi);

			//>! save image
			string filename = "grid_" + to_string(l_n) + ".png";
			imwrite(filename, gridImg);
			imshow(filename,gridImg);
			++l_n;
		}
	}

    //>! check image
	Mat img0_sec = imread("./grid_0.png", 0);
	Mat img1_sec = imread("./grid_1.png", 0);
	Mat img2_sec = imread("./grid_2.png", 0);
	Mat img3_sec = imread("./grid_3.png", 0);
	Mat img4_sec = imread("./grid_4.png", 0);
	Mat img5_sec = imread("./grid_5.png", 0);
	Mat outImg, outImg0, outImg1, outImg2;
    hconcat(img0_sec,img1_sec,outImg0);
	hconcat(img2_sec,img3_sec,outImg1);
	hconcat(img4_sec,img5_sec,outImg2);
	vconcat(outImg0,outImg1,outImg);

	//>! using cv::Rect
	Rect roi(l_starX_i, l_starY_i, l_width_i, l_height_i);
	Mat croppedImage = image(roi);
    croppedImage = image(Range(l_starY_i, l_starY_i + l_height_i),Range(l_starX_i,l_starX_i + l_width_i));

	//>! printf images
	imshow("origin_image", image); // origin image
	imshow("cur_image", croppedImage);
	imshow("pick_image",outImg);

	//>! wait for time
	waitKey();
	return 0;
}
//=================================================================//
//                           NO_MORE                               //
//=================================================================//