#include <string>
#include "opencv2/opencv.hpp"
#include "cascade_Base.hpp"

#ifndef AUTHENTICATION_SYSTEM_CASCADE_DETECT_CV_H
#define AUTHENTICATION_SYSTEM_CASCADE_DETECT_CV_H


class Cascade_basic: public Cascade_base{

public:
	Cascade_basic();
	~Cascade_basic();

    void load_cascade_face(std::string path);

    void detectMultiScale(cv::Mat image, std::vector<cv::Rect> &faces, double scaleFactor, double minNeighbors, double flags, cv::Size minSize);


void EyedetectMultiScale(cv::Mat image, std::vector <cv::Rect> &eyes, double scaleFactor, double minNeighbors, double flags, cv::Size minSize);


private:
	cv::CascadeClassifier cascade;
};


#endif //AUTHENTICATION_SYSTEM_CASCADE_DETECT_CV_H
