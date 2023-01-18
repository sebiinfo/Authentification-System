#include <string>
#include "opencv2/opencv.hpp"
#include "cascade_Base.hpp"
#ifndef AUTHENTICATION_SYSTEM_CASCADE_DETECT_CV_H
#define AUTHENTICATION_SYSTEM_CASCADE_DETECT_CV_H


class cascade_detect_cv: public cascade_Base
        {
public:
    cascade_detect_cv();
    ~cascade_detect_cv();
    void load(std::string path);
    void detectMultiScale(cv::Mat image, std::vector<cv::Mat> &faces, double scaleFactor, double minNeighbors, double flags, cv::Size minSize);
private:
    cv::CascadeClassifier cascade;
};


#endif //AUTHENTICATION_SYSTEM_CASCADE_DETECT_CV_H
