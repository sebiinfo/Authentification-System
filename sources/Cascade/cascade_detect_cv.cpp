#include "cascade_detect_cv.hpp"

#define test 0

#if test==0

std::string path_face = "/usr/local/share/opencv4/haarcascades/haarcascade_frontalface_default.xml";
std::string path_eye = "/usr/local/share/opencv4/haarcascades/haarcascade_eye.xml";

#endif


Cascade_detect_cv::Cascade_detect_cv()
{
	cascade = cv::CascadeClassifier();
	cascade.load(path_face);
}

Cascade_detect_cv::~Cascade_detect_cv(){}


void Cascade_detect_cv::load(std::string path){
    cascade.load(path);
}


void Cascade_detect_cv::detectMultiScale(cv::Mat image, std::vector<cv::Rect> &faces, double scaleFactor, double minNeighbors, double flags, cv::Size minSize){

    cascade.detectMultiScale(image,faces, scaleFactor, minNeighbors, flags, minSize);
}

// void Cascade_detect_cv::detectMultiScale(cv::Mat image, std::vector<cv::Rect> &faces)
// {
//     detectMultiScale(image,faces, 1, 4, 0, cv::Size(30,30));
// }

void Cascade_detect_cv::Special_Transform()
{
    return;
}
