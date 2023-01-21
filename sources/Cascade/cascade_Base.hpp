#include <opencv2/core/mat.hpp>
#include <iostream>

#ifndef AUTHENTICATION_SYSTEM_CASCADE_OBJECT_DETECTOR_H
#define AUTHENTICATION_SYSTEM_CASCADE_OBJECT_DETECTOR_H

class Cascade_base {
public:

	Cascade_base();
	~ Cascade_base();

    virtual void detectMultiScale(cv::Mat image, std::vector<cv::Rect> &faces, double scaleFactor, double minNeighbors, double flags, cv::Size minSize);
	virtual void EyedetectMultiScale(cv::Mat image, std::vector<cv::Rect> &faces, double scaleFactor, double minNeighbors, double flags, cv::Size minSize);


private:
	int heigth;
	int width;
	int padding;



};


#endif //AUTHENTICATION_SYSTEM_CASCADE_OBJECT_DETECTOR_H
