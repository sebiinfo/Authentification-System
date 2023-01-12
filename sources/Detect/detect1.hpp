#include <opencv2/core/mat.hpp>
#include <filesystem>
#include <iostream>
#include "../Cropimage/cropimage.hpp"

#ifndef DETECT_HPP
#define DETECT_HPP

double adjustThreshold(double meanIntensity);

void normalizeIntensities(cv::Mat image);

// Returns true if both eyes are open, else false
bool isEyeOpen(cv::Mat frame);

// Returns true if a face was detected, else false
bool isFace(cv::Mat frame);

// Returns ture if an eye was detected, else false
bool isEye(cv::Mat);

// Returns an array of cv::Rect corresponding to coordinates of faces recognized in the image
std::vector<cv::Rect> detectFaces(cv::Mat image, int dim_face);

// Returns an array of cv::Rect corresponding to coordinates of eyes recognized in the image
std::vector<cv::Rect> detectEyes(cv::Mat, int dim_eye);

bool openEyes(cv::Mat image);

// Checks if an image is comform ( face + open eyes )
bool conform(cv::Mat image);

//Returns an array containing only the conform images
std::vector<cv::Mat> conformArray (std::vector<cv::Mat> faces);

#endif // DETECT_HPP
