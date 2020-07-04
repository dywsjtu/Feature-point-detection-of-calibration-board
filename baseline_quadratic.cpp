#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
// #include "opencv2/"
#include <iostream>
using namespace cv;
using namespace std;
Mat src, src_gray, cp;
int maxCorners = 25;
RNG rng(12345);
void goodFeaturesToTrack_Demo(int, void *);

int main(int argc, char **argv)
{
    src = imread(argv[1]);
    if (src.empty())
    {
        cout << "Could not open or find the image!\n"
             << endl;
        return -1;
    }
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    goodFeaturesToTrack_Demo(0, 0);
    imwrite(argv[2], cp);
    return 0;
}
void goodFeaturesToTrack_Demo(int, void *)
{
    maxCorners = MAX(maxCorners, 1);
    vector<Point2f> corners;
    double qualityLevel = 0.01;
    double minDistance = 10;
    int blockSize = 3, gradientSize = 3;
    bool useHarrisDetector = false;
    double k = 0.04;
    cp = src.clone();
    goodFeaturesToTrack(src_gray,
                        corners,
                        maxCorners,
                        qualityLevel,
                        minDistance,
                        Mat(),
                        blockSize,
                        gradientSize,
                        useHarrisDetector,
                        k);
    cout << "** Number of corners detected: " << corners.size() << endl;
    int radius = 4;
    for (size_t i = 0; i < corners.size(); i++)
    {
        circle(cp, corners[i], radius, Scalar(rng.uniform(0, 255), rng.uniform(0, 256), rng.uniform(0, 256)), FILLED);
    }
    Size winSize = Size(5, 5);
    Size zeroZone = Size(-1, -1);
    TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 40, 0.001);
    cornerSubPix(src_gray, corners, winSize, zeroZone, criteria);
    // To do //

    // quadratic fitting //
    for (size_t i = 0; i < corners.size(); i++) {
        cout << " -- Refined Corner [" << i << "]  (" << corners[i].x << "," << corners[i].y << ")" << endl;
    }
}