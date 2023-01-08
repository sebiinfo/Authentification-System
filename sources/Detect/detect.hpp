#include <opencv2/opencv.hpp>
#ifndef DETECT_HPP
#define DETECT_HPP

double adjustThreshold(cv::Mat frame);
bool isEyeOpen(cv::Mat frame);

#endif // DETECT_HPP
