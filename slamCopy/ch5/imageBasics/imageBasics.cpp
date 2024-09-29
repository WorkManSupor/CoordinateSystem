#include "iostream"
#include "chrono"
using namespace std;

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;

int main(int argc, char **argv)
{
    // read image
    Mat image = imread(argv[1]);

    // check null
    if (image.data == nullptr)
    {
        cerr << "files" << argv[1] << "nullprr" << endl;
        return 0;
    }

    // printf message of image
    cout << "Width :" << image.cols << endl;
    cout << "high: " << image.rows << endl;
    cout << "channels:" << image.channels() << endl;

    //>! show image
    imshow("origin image", image);
    waitKey(0);

    // no target image type
    if (image.type() != CV_8UC1 && image.type() != CV_8UC3)
    {
        cout << "please imput RGB/GRAY image" << endl;
        return 0;
    }

    // lookover every pixel of image
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    for (size_t y = 0; y < image.rows; y++)
    {
        for (size_t x = 0; x < image.cols; x++)
        {
            // get every pix of image
            unsigned char *row_ptr = image.ptr<unsigned char>(y);
            unsigned char *data_ptr = &row_ptr[x * image.channels()];
        }
    }
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast < chrono::duration<double>> (t2 - t1);
    cout << "look over image cost time:" << time_used.count() << "s." << endl;

    Mat image_another = image;
    image_another(Rect(0, 0, 100, 100)).setTo(0);
    imshow("cor_image", image);
    waitKey(0);
    Mat image_clone = image.clone();
    image_clone(Rect(0, 0, 100, 100)).setTo(255);
    imshow("image", image);
    imshow("image_clone", image_clone);
    waitKey(0);

    destroyAllWindows();
    return 0;
}