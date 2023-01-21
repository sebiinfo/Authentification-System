#include "cascade_detect_cv.hpp"

#define test 0

#if test==0

#endif


Cascade_basic::Cascade_basic()
{

	std::string face = "C:\\Authentification-System\\sources\\Cascade\\haarcascades\\haarcascade_frontalface_default.xml";
// std::string eye = "/usr/local/share/opencv4/haarcascades/haarcascade_eye.xml";

	cascade = cv::CascadeClassifier();
	cascade.load(face);
}

Cascade_basic::~Cascade_basic(){}


void Cascade_basic::load_cascade_face(std::string path){
    cascade.load(path);
}


void Cascade_basic::detectMultiScale(cv::Mat image, std::vector<cv::Rect> &faces, double scaleFactor, double minNeighbors, double flags, cv::Size minSize){

    cascade.detectMultiScale(image,faces, scaleFactor, minNeighbors, flags, minSize);
}

void Cascade_basic::EyedetectMultiScale(cv::Mat image, std::vector<cv::Rect> &eyes, double scaleFactor, double minNeighbors, double flags, cv::Size minSize){
    return;
}
