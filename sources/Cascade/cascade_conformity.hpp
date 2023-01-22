#include <iostream>
#include <vector>
//#include "opencv2/opencv.hpp"
#include "cascade_detect_cv.hpp"
#include <opencv2/objdetect/objdetect.hpp>
#include "cascade_Base.hpp"
#ifndef AUTHENTICATION_SYSTEM_CONFORMITY_H
#define AUTHENTICATION_SYSTEM_CONFORMITY_H


class Cascade_conformity: public Cascade_base{
public:
    Cascade_conformity();
    ~Cascade_conformity();

    void load_cascade_face(std::string path_f);
    void load_cascade_eyes(std::string path_e);

    void detectMultiScale(cv::Mat image, std::vector<cv::Rect> &faces, double scaleFactor, double minNeighbors, double flags, cv::Size minSize);
    void EyedetectMultiScale(cv::Mat image, std::vector<cv::Rect> &eyes, double scaleFactor, double minNeighbors, double flags, cv::Size minSize);

private:
	cv::CascadeClassifier cascade_face;
	cv::CascadeClassifier cascade_eyes;


    void isEye(cv::Mat image, std::vector<cv::Rect> &faces);

};


#endif //AUTHENTICATION_SYSTEM_CONFORMITY_H
