#ifndef RESCALE_HPP
#define RESCALE_HPP

#include <opencv2/opencv.hpp>


// Rescales the image using bilinear interpolation and returns the resized image
cv::Mat rescaleImage(cv::Mat image, int newWidth, int newHeight);


#endif // RESCALE_HPP
