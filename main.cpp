#include <iostream>
//#include "tests.cpp"
#include "sources/Cropimage/cropimage.hpp"

int main() {
    std::cout << "Hello world" << std::endl;

    cv::Mat frame;
    frame = getFrame();

    showFrame(frame);

//    test();
}
