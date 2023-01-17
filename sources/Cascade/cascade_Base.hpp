#include <opencv2/core/mat.hpp>
#include <iostream>

#ifndef AUTHENTICATION_SYSTEM_CASCADE_OBJECT_DETECTOR_H
#define AUTHENTICATION_SYSTEM_CASCADE_OBJECT_DETECTOR_H


class cascade_Base {
public:
    cascade_Base();
    ~ cascade_Base();
    virtual void detectMultiScale(cv::Mat image, cv::Rect &faces, double scaleFactor, double minNeighbors, double flags, cv::Size minSize);

};


#endif //AUTHENTICATION_SYSTEM_CASCADE_OBJECT_DETECTOR_H
