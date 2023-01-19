#include <opencv2/core/mat.hpp>
#include <iostream>

#ifndef AUTHENTICATION_SYSTEM_CASCADE_OBJECT_DETECTOR_H
#define AUTHENTICATION_SYSTEM_CASCADE_OBJECT_DETECTOR_H


class cascade_Base {
public:
    cascade_Base();
    ~ cascade_Base();

    /////////////////////////////( Input image ,
    virtual void detectMultiScale(cv::Mat image, std::vector<cv::Mat> &faces, double scaleFactor, double minNeighbors, double flags, cv::Size minSize);
    std::vector<cv::Rect> vect_faces;


    void Crop(cv::Mat &image);
    void Rescale(cv::Mat &image);
    cv::Mat Transform();

int height;
int width;
int padding;
};


#endif //AUTHENTICATION_SYSTEM_CASCADE_OBJECT_DETECTOR_H
