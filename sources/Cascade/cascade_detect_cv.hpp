#include <string>
#include "opencv2/opencv.hpp"
#include "cascade_Base.hpp"

#ifndef AUTHENTICATION_SYSTEM_CASCADE_DETECT_CV_H
#define AUTHENTICATION_SYSTEM_CASCADE_DETECT_CV_H


class Cascade_detect_cv: public cascade_Base{

public: // Public methods
    Cascade_detect_cv();
    ~Cascade_detect_cv();
    void load(std::string path);

    void detectMultiScale(cv::Mat image, std::vector<cv::Rect> &faces, double scaleFactor, double minNeighbors, double flags, cv::Size minSize);
//	virtual void detectMultiScale(cv::Mat image, std::vector<cv::Rect> &faces, double scaleFactor, double minNeighbors, double flags, cv::Size minSize);
    // void detectMultiScale(cv::Mat image, std::vector<cv::Rect> &faces);
	void Special_Transform();

private: // Private methods

public: // Public attributes

cv::CascadeClassifier cascade;


private: // Private attributes


};


#endif //AUTHENTICATION_SYSTEM_CASCADE_DETECT_CV_H
