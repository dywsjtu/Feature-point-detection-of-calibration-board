#ifndef _OPENCV_INCLUDE_
#define _OPENCV_INCLUDE_

#include <opencv2/opencv.hpp>

#endif

void CornerSubPix(cv::Mat src, std::vector<cv::Point2f> &corners,
                  int win, int max_iter, double epsilon)
{
    int win_w = win * 2 + 1, win_h = win * 2 + 1;
    double eps = epsilon * epsilon;
    if (corners.size() == 0)
        return;

    cv::Mat maskm(win_h, win_w, CV_32F), subpix_buf(win_h + 2, win_w + 2, CV_32F);
    float *mask = maskm.ptr<float>();
    for (int i = 0; i < win_h; i++)
    {
        float y = (float)(i - win) / win;
        float vy = std::exp(-y * y);
        for (int j = 0; j < win_w; j++)
        {
            float x = (float)(j - win) / win;
            mask[i * win_w + j] = (float)(vy * std::exp(-x * x));
        }
    }

    for (int pt_i = 0; pt_i < corners.size(); ++pt_i)
    {
        cv::Point2f cT = corners[pt_i], cI = cT;
        for (int iter = 0; iter < max_iter; ++iter)
        {
            double a = 0, b = 0, c = 0, bb1 = 0, bb2 = 0;
            getRectSubPix(src, cv::Size(win_w + 2, win_h + 2), cI, subpix_buf, subpix_buf.type());
            const float *subpix = &subpix_buf.at<float>(1, 1);
            for (int i = 0; i < win_h; ++i, subpix += win_w + 2)
            {
                double py = i - win;
                for (int j = 0; j < win_w; ++j)
                {
                    double m = mask[i * win_w + j];
                    double tgx = subpix[j + 1] - subpix[j - 1];
                    double tgy = subpix[j + win_w + 2] - subpix[j - win_w - 2];
                    double gxx = tgx * tgx * m;
                    double gxy = tgx * tgy * m;
                    double gyy = tgy * tgy * m;
                    double px = j - win;
                    
                    a += gxx;
                    b += gxy;
                    c += gyy;
                    bb1 += gxx * px + gxy * py;
                    bb2 += gxy * px + gyy * py;
                }
            }

            double det = a * c - b * b;
            if (fabs(det) <= DBL_EPSILON * DBL_EPSILON)
                break;

            double scale = 1.0 / det;
            double dx = c * scale * bb1 - b * scale * bb2;
            double dy = a * scale * bb2 - b * scale * bb1;
            // std::cout.precision(10);
            // std::cout << "x: " << cI.x << ", y: " << cI.y << std::endl;
            // std::cout.precision(6);
            cI.x = (float)(cI.x + dx);
            cI.y = (float)(cI.y + dy);
            if (dx * dx + dy * dy < eps || cI.x < 0 || cI.x >= src.cols || cI.y < 0 || cI.y >= src.rows)
                break;
        }
        if (fabs(cI.x - cT.x) > win || fabs(cI.y - cT.y) > win)
            cI = cT;
        corners[pt_i] = cI;
    }
}