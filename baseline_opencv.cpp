#ifndef _OPENCV_INCLUDE_
#define _OPENCV_INCLUDE_

#include <opencv2/opencv.hpp>

#endif

#include <iostream>

#include "CornerSubPixel.hpp"
#include "CornerPixel.hpp"

using namespace cv;
using namespace std;

Mat src, src_gray, cp;
int maxCorners = 20;
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
    int useHarrisDetector = 0;
    double k = 0.04;
    cp = src.clone();
    CornerPixel(src_gray,
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
    int winSize = 5;
    int maxCount = 40;
    double epsilon = 0.001;
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    CornerSubPix(src_gray, corners, winSize, maxCount, epsilon);

    // Size winSize = Size(5, 5);
    // Size zeroZone = Size(-1, -1);
    // TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 40, 0.001);
    // cornerSubPix(src_gray, corners, winSize, zeroZone, criteria);

    for (size_t i = 0; i < corners.size(); i++)
    {
        cout << " -- Refined Corner [" << i << "]  (" << corners[i].x << "," << corners[i].y << ")" << endl;
    }
}
