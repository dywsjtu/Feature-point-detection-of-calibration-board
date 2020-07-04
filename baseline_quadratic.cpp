#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
Mat src, src_gray, cp, blr;
int maxCorners = 25;
RNG rng(12345);
void goodFeaturesToTrack_Demo(int, void *);
void quadraticSubPix(Mat image, vector<Point2f> corners, Size winSize);

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
    imwrite(argv[2], blr);
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
    // Size zeroZone = Size(-1, -1);
    // TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 40, 0.001);

    // To do //
    quadraticSubPix(src_gray, corners, winSize);

    // quadratic fitting //
    for (size_t i = 0; i < corners.size(); i++)
    {
        cout << " -- Refined Corner [" << i << "]  (" << corners[i].x << "," << corners[i].y << ")" << endl;
    }
}

void quadraticSubPix(Mat image, vector<Point2f> corners, Size winSize)
{
    GaussianBlur(image, blr, Size(5, 5), 0, 0);
    for (size_t i = 0; i < corners.size(); i++)
    {
        
    }
}