// #include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <iostream>
using namespace cv;
int main()
{
    Mat img=imread("resource/texture/container.jpg");
    imshow("image",img);
    waitKey();
    // printf("Congratulasions! It works!\n");
    // system("pause");
    return 0;
}