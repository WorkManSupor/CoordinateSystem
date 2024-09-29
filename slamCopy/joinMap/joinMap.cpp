#include "iostream"
#include "fstream"
using namespace std;

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;

#include "Eigen/Geometry"
using namespace Eigen;

#include "boost/format.hpp" // for formating strings
using namespace boost;

#include "pcl/point_types.h"
#include "pcl/io/pcd_io.h"
#include "pcl/visualization/pcl_visualizer.h"
using namespace pcl;

int main(int argc, char **argv)
{
    vector<Mat> colorImgs, depthImgs;                       // RGB , GRAY
    vector<Isometry3d, aligned_allocator<Isometry3d>> poses; // camera pose and attitude
    ifstream fin("./pose.txt");

    if (!fin)
    {
        cerr << "please ensure pose.txt in target document." << endl;
        return 1;
    }

    for (int i = 0; i < 5; i++)
    {
        boost::format fmt("./%s/%d.%s");
        colorImgs.push_back(imread((fmt % "color" % (i + 1) % "png").str()));
        depthImgs.push_back(imread((fmt % "depth" % (i + 1) % "pgm").str(), -1)); // suing -1, read origin image

        double data[7] = {0};
        for (auto &d : data)
            fin >> d;
        Quaterniond q(data[6], data[3], data[4], data[5]);
        Isometry3d T(q);
        T.pretranslate(Vector3d(data[0], data[1], data[2]));
        poses.push_back(T);
    }

    double cx = 325.5;
    double cy = 253.5;
    double fx = 518.0;
    double fy = 519.0;
    double depthScale = 1000.0;

    cout << "transform image to cloud points" << endl;
    // set could point type: here is XYZRGB
    typedef PointXYZRGB PointT;
    typedef PointCloud<PointT> PointCloud;

    PointCloud::Ptr pointCloud(new PointCloud);
    for (int i = 0; i < 5; i++)
    {
        cout << "transform image" << i + 1 << endl;
        Mat color = colorImgs[i];
        Mat depth = depthImgs[i];
        Isometry3d T = poses[i];
        for (int v = 0; v < color.rows; v++)
        {
            for (int u = 0; u < color.cols; u++)
            {
                unsigned int d = depth.ptr<unsigned short>(v)[u];
                if (d == 0)
                    continue;
                Vector3d point;
                point[2] = double(d) / depthScale;
                point[0] = (u - cx) * point[2] / fx;
                point[1] = (v - cy) * point[2] / fy;
                Vector3d pointWorld = T * point;

                PointT p;
                p.x = pointWorld[0];
                p.y = pointWorld[1];
                p.z = pointWorld[2];
                p.b = color.data[v * color.step + u * color.channels()];
                p.g = color.data[v * color.step + u * color.channels() + 1];
                p.r = color.data[v * color.step + u * color.channels() + 2];
                pointCloud->points.push_back(p);
            }
        }
    }
    pointCloud->is_dense = false;
    cout << "total cloud point" << pointCloud->size() << "sizeNum" << endl;
    pcl::io::savePCDFileBinary("map.pcd", *pointCloud);
    return 0;
}