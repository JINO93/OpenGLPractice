// #include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <iostream>
using namespace cv;
int main()
{
    Mat img=imread("resource/container.jpg");
    imshow("image",img);
    waitKey();
    // printf("Congratulasions! It works!\n");
    return 0;
}