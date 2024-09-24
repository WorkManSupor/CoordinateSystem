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

void ChangeImgBG();
Mat HandleImgData(Mat &img);

int main(int argc, char **argv)
{
	//>! change base picture
    ChangeImgBG();

	//>! load source jpg
	Mat image = imread("base.jpg");
	if (!image.data)
	{
		cout << "image load error !" << endl;
		return -1;
	}

    imshow("ori_image",image);	

	//>! get the max pxile size
	unsigned int l_rows = image.rows;
	unsigned int l_cols = image.cols;
	unsigned int l_max = (l_rows > l_cols) ? l_rows : l_cols;
	unsigned int l_min = (l_rows > l_cols) ? l_cols : l_rows;

	//>! set the size of image
	Mat imageCor;
	Size l_srcSize = Size(l_min, l_max);
	resize(image, image, l_srcSize, 0, 0, INTER_LINEAR);
	cout << image.size() << endl;

	//>! printf images
	imshow("resize_image", image); // origin image

	//>! wait for time
	waitKey();
	return 0;
}
/*
图片背景替换
知识点：分水岭分割、高斯模糊
处理步骤：数据组装-KMeans分割-背景消除-生成遮罩-模糊-输出
*/
void ChangeImgBG()
{
    const char* win1 = "window1";
    const char* win2 = "window2";
    const char* win3 = "window3";
    const char* win4 = "window4";
    const char* win5 = "window5";
    const char* win6 = "window6";
    namedWindow(win1, WINDOW_AUTOSIZE);//创建窗口 win1
    namedWindow(win2, WINDOW_AUTOSIZE);//创建窗口 win2
    namedWindow(win3, WINDOW_AUTOSIZE);//创建窗口 win3
    namedWindow(win4, WINDOW_AUTOSIZE);//创建窗口 win4
    namedWindow(win5, WINDOW_AUTOSIZE);//创建窗口 win5
    namedWindow(win6, WINDOW_AUTOSIZE);//创建窗口 win6

    Mat img1, img2;
    //加载图片
    img1 = imread("base.jpg");
    if (img1.empty())
    {
        cout << "image not found..." << endl;
        exit(0);//如果图片不存在，退出程序
    }
    img2 = img1.clone();
    //显示原始图片
    imshow(win1, img1);
    //组装数据
    Mat points = HandleImgData(img1);

    //Kmeans处理
    int numCluster = 4;
    Mat labels;
    Mat centers;
    TermCriteria termCriteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1);

    kmeans(points, numCluster, labels, termCriteria, 3, KMEANS_PP_CENTERS, centers);
    //遮罩
    Mat mask = Mat::zeros(img1.size(), CV_8UC1);
    int index = img1.rows * 2 + 2;
    int cindex = labels.at<int>(index, 0);//背景设置为0
    int height = img1.rows;
    int width = img1.cols;

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            index = row * width + col;
            int label = labels.at<int>(index, 0);
            if (label == cindex)
            {
                img2.at<Vec3b>(row, col)[0] = 0;
                img2.at<Vec3b>(row, col)[1] = 0;
                img2.at<Vec3b>(row, col)[2] = 0;
                mask.at<uchar>(row, col) = 0;
            }
            else
            {
                mask.at<uchar>(row, col) = 255;
            }
        }
    }

    //腐蚀
    Mat k = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
    erode(mask, mask, k);
    imshow(win4, mask);

    //高斯模糊
    GaussianBlur(mask, mask, Size(3, 3), 0, 0);
    imshow(win5, mask);

    //通道混合
    RNG rng(12345);


    //背景颜色调整
    Vec3b color;
    /*color[0] = rng.uniform(255, 255);
    color[1] = rng.uniform(255, 255);
    color[2] = rng.uniform(255, 255);*/
    color[0] = 255;
    color[1] = 255;
    color[2] = 255;

    Mat result(img1.size(), img1.type());

    double d1 = 0.0;
    int r = 0, g = 0, b = 0;
    int r1 = 0, g1 = 0, b1 = 0;
    int r2 = 0, g2 = 0, b2 = 0;


    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int m = mask.at<uchar>(row, col);
            if (m == 255)
            {
                result.at<Vec3b>(row, col) = img1.at<Vec3b>(row, col);//前景
            }
            else if (m == 0)
            {
                result.at<Vec3b>(row, col) = color;//背景
            }
            else
            {
                d1 = m / 255.0;
                b1 = img1.at<Vec3b>(row, col)[0];
                g1 = img1.at<Vec3b>(row, col)[1];
                r1 = img1.at<Vec3b>(row, col)[2];

                b2 = color[0];
                g2 = color[1];
                r2 = color[2];

                b = b1 * d1 + b2 * (1.0 - d1);
                g = g1 * d1 + g2 * (1.0 - d1);
                r = r1 * d1 + r2 * (1.0 - d1);

                result.at<Vec3b>(row, col)[0] = b;
                result.at<Vec3b>(row, col)[1] = g;
                result.at<Vec3b>(row, col)[2] = r;
            }
        }
    }

    //输出
    imshow(win2, mask);
    imshow(win3, img2);
    imshow(win6, result);
    //保存处理后的图片
    imwrite("pph_bg_white.jpg", result);
}

//组装样本数据
Mat HandleImgData(Mat &img)
{
    int width = img.cols;
    int height = img.rows;
    int count1 = width * height;
    int channels1 = img.channels();

    Mat points(count1, channels1, CV_32F, Scalar(10));
    int index = 0;
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            index = row * width + col;
            Vec3b bgr = img.at<Vec3b>(row, col);
            points.at<float>(index, 0) = static_cast<int>(bgr[0]);
            points.at<float>(index, 1) = static_cast<int>(bgr[1]);
            points.at<float>(index, 2) = static_cast<int>(bgr[2]);
        }
    }
    return points;
}

//=================================================================//
//                           NO_MORE                               //
//=================================================================//