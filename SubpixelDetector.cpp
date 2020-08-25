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
int maxCorners = 16;
RNG rng(12345);
bool point_comparator(const cv::Point2f &a, const cv::Point2f &b);

vector<Point2f> findCorner(int, void *);
vector<Point2f> subPixel(vector<Point2f>);

int main(int argc, char **argv)
{
    Mat source = imread(argv[1]);
    if (source.empty())
    {
        cout << "Could not open or find the image!\n"
             << endl;
        return -1;
    }
    // src = source;
    resize(source, src, Size(1280, 720));
    maxCorners = atoi(argv[3]);
    cout << "Size: " << src.size() << ";" << maxCorners << endl;
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    vector<Point2f> corners = findCorner(0, 0);
    corners = subPixel(corners);
    imwrite(argv[2], cp);
    return 0;
}

vector<Point2f> findCorner(int, void *)
{
    maxCorners = MAX(maxCorners, 1);
    vector<Point2f> corners;
    double qualityLevel = 0.02;
    double minDistance = 5;
    int blockSize = 5, gradientSize = 5;
    int useHarrisDetector = 1;
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

    // circle(src_gray, corners[1], 5, Scalar(0, 0, 255), FILLED);

    // for (size_t i = 0; i < corners.size(); i++)
    // {
    //     // cout << " -- Refined Corner [" << i << "]  (" << corners[i].x << "," << corners[i].y << ")" << endl;
    //     cout << "[" << i << "]" << std::endl
    //          << corners[i].x << std::endl
    //          << corners[i].y << endl;
    // }
    // int radius = 2;
    // for (size_t i = 0; i < corners.size(); i++)
    // {
    //     circle(cp, corners[i], radius, Scalar(rng.uniform(0, 255), rng.uniform(0, 256), rng.uniform(0, 256)), FILLED);
    // }

    return corners;
}

vector<Point2f> subPixel(vector<Point2f> corners)
{
    int winSize = 5;
    int maxCount = 200;
    double epsilon = 0.0001;
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    CornerSubPix(src_gray, corners, winSize, maxCount, epsilon);

    // Size winSize = Size(5, 5);
    // Size zeroZone = Size(-1, -1);
    // TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 40, 0.001);
    // cornerSubPix(src_gray, corners, winSize, zeroZone, criteria);

    std::sort(corners.begin(), corners.end(), point_comparator);

    for (size_t i = 0; i < corners.size(); i++)
    {
        // cout << " -- Refined Corner [" << i << "]  (" << corners[i].x << "," << corners[i].y << ")" << endl;
        cout << "[" << i << "]" << std::endl << corners[i].x << std::endl << corners[i].y << endl;
    }

    int radius = 5;
    for (size_t i = 0; i < corners.size(); i++)
    {
        circle(cp, corners[i], radius, Scalar(rng.uniform(0, 255), rng.uniform(0, 256), rng.uniform(0, 256)), FILLED);
    }

    return corners;
}

bool point_comparator(const cv::Point2f &a, const cv::Point2f &b) {
    return (a.y + 10.0 < b.y) || ((a.y < b.y + 10.0) && a.x < b.x);
}