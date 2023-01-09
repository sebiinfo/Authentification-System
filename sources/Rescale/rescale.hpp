#ifndef RESCALE_HPP
#define RESCALE_HPP

#include <opencv2/core/mat.hpp>


// Rescales the image using bilinear interpolation and returns the resized image
cv::Mat rescaleImage(cv::Mat image, int newWidth, int newHeight);

// Rescale an array of image using rescaleImage
std::vector<cv::Mat> rescaleArray(std::vector<cv::Mat> array, int newWidhgt, int newHeight);

#endif // RESCALE_HPP
