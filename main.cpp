#include <iostream>
#include <opencv2/opencv.hpp>
//#include "tests.cpp"
#include "detect.hpp"
#include "sources/Cropimage/cropimage.hpp"

int main() {
    cv::Mat frame = cv::imread("testimg.jpg");
    bool eyeOpen = isEyeOpen(frame);
    std::cout << "Eye open: " << eyeOpen << std::endl;
    return 0;
}
