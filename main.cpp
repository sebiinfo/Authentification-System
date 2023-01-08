#include <iostream>
#include <opencv2/opencv.hpp>
//#include "tests.cpp"
#include "detect.hpp"
#include "rescale.hpp"
#include "sources/Cropimage/cropimage.hpp"

int main() {
    cv::Mat frameclosed = cv::imread("C:\\Users\\USER\\CLionProjects\\Authentification-System\\Authentification-System\\agathaclosed.jpg");
    frameclosed=rescaleImage(frameclosed, 224,224);
    bool eyeOpen0 = isEyeOpen(frameclosed);
    cv::Mat frameopen = cv::imread("C:\\Users\\USER\\CLionProjects\\Authentification-System\\Authentification-System\\agathaopen.jpg");
    frameopen=rescaleImage(frameopen, 224,224);
    bool eyeOpen1 = isEyeOpen(frameopen);
    std::cout << "Eye closed: (1 if eye is open) " << eyeOpen0 << std::endl;
    std::cout << "Eye opened: (1 if eye is open) " << eyeOpen1 << std::endl;
    return 0;
}
