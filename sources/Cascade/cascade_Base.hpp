#include <opencv2/core/mat.hpp>
#include <iostream>

#ifndef AUTHENTICATION_SYSTEM_CASCADE_OBJECT_DETECTOR_H
#define AUTHENTICATION_SYSTEM_CASCADE_OBJECT_DETECTOR_H


class cascade_Base {
public:
    cascade_Base();
    ~ cascade_Base();

    /////////////////////////////( Input image ,
    void load(std::string path);
    virtual void detectMultiScale(cv::Mat image, std::vector<cv::Rect> &faces, double scaleFactor, double minNeighbors, double flags, cv::Size minSize);
    void Special_transform();



//    bool is_pad(cv::Mat image, cv::Rect face);
//    void Crop(cv::Mat &image,cv::Rect face);
//    void Rescale(cv::Mat &image);
//    cv::Mat Transform();

};


#endif //AUTHENTICATION_SYSTEM_CASCADE_OBJECT_DETECTOR_H
