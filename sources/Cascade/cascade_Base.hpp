#include <opencv2/core/mat.hpp>
#include <iostream>

#ifndef AUTHENTICATION_SYSTEM_CASCADE_OBJECT_DETECTOR_H
#define AUTHENTICATION_SYSTEM_CASCADE_OBJECT_DETECTOR_H

class cascade_Base {
public:
    cascade_Base();
    ~ cascade_Base();

    void load(std::string path);
    virtual void detectMultiScale(cv::Mat image, std::vector<cv::Rect> &faces, double scaleFactor, double minNeighbors, double flags, cv::Size minSize);
    // virtual void detectMultiScale(cv::Mat image, std::vector<cv::Rect> &faces);


    void Special_Transform(); // Transform Specific to the cascade.



// Attributes of the class
public: // Shared with children

    std::vector<cv::Rect> vect_faces;


private: // Kept for itself
	int heigth;
	int width;
	int padding;



};


#endif //AUTHENTICATION_SYSTEM_CASCADE_OBJECT_DETECTOR_H
