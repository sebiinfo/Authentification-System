#include <opencv2/opencv.hpp>
#include <filesystem>
#ifndef DETECT_HPP
#define DETECT_HPP

double adjustThreshold(double meanIntensity);
bool isEyeOpen(cv::Mat frame);
void normalizeIntensities(cv::Mat image);
bool detectEyes(cv::Mat image);

#endif // DETECT_HPP
