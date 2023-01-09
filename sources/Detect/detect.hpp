#include <opencv2/core/mat.hpp>
#include <filesystem>

#ifndef DETECT_HPP
#define DETECT_HPP

double adjustThreshold(double meanIntensity);

bool isEyeOpen(cv::Mat frame);

void normalizeIntensities(cv::Mat image);

// Returns true if eyes were detected
bool detectEyes(cv::Mat image);

// Returns array of cv::Rect corresponding to coordinates of faces recognized in the image
std::vector<cv::Rect> detectFaces(cv::Mat image);

#endif // DETECT_HPP
