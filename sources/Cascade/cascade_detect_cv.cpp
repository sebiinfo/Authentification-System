//
// Created by USER on 16/01/2023.
//

#include "cascade_detect_cv.hpp"
cascade_detect_cv::cascade_detect_cv(){}
cascade_detect_cv::~cascade_detect_cv(){}
void cascade_detect_cv::load(std::string path){
    cascade.load(path);
}
void cascade_detect_cv::detectMultiScale(cv::Mat image, std::vector<cv::Rect> &faces, double scaleFactor, double minNeighbors, double flags, cv::Size minSize){

    cascade.detectMultiScale(image,faces, scaleFactor, minNeighbors, flags, minSize);
}


std::vector<cv::Mat> cascade_detect_cv::Transform(cv::Mat image){

    std::vector<cv::Rect> faces;
    std::vector<cv::Mat> images;
\
    detectMultiScale(image,faces,1.0,4.0,0,cv::Size(30,30));

    images = Crop(image,faces);

    Rescale(images);

    return images;
}
