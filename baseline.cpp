#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
using namespace cv;

Mat src, dst, src_gray;

char *window_name = "Demo";

/**
 * @Principal function
 */
int main(int argc, char **argv)
{

    ///Read a picture without changing the color type of the picture itself (read in DOS mode)
    src = imread(argv[1], 1);

    ///Convert pictures to grayscale pictures
    cvtColor(src, src_gray, COLOR_RGB2GRAY);

    namedWindow(window_name, WINDOW_AUTOSIZE);

    imshow(window_name, src_gray);

    while (true)
    {
        int c;
        c = waitKey(20);
        if (27 == (char)c)
        {
            break;
        }
    }
}