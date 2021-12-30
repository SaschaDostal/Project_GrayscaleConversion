#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <cstdio>
#include <iostream>
#include <sys/time.h>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    char *filename = (char *)"BenchmarkPictureL.jpg";
    Mat rgb_img = imread(filename, 1);
    Mat gray_img;

    struct timeval start;
    gettimeofday(&start, 0);

    cv::cvtColor(rgb_img, gray_img, COLOR_BGR2GRAY);

    struct timeval end;
    gettimeofday(&end, 0);
    long lsec = end.tv_sec - start.tv_sec;
    long lusec = end.tv_usec - start.tv_usec;
    double sec = (lsec + lusec / 1000000.0);
    printf("%8.6f seconds\n", sec);

    imwrite("grayscale_opencv.jpg", gray_img);
}