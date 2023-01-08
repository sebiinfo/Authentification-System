#include "rescale.hpp"

#include <opencv2/opencv.hpp>

// Rescales the image using bilinear interpolation and returns the resized image
cv::Mat rescaleImage(cv::Mat image, int newWidth, int newHeight) {
    // Create a Mat object to hold the resized image
    cv::Mat resized(newHeight, newWidth, image.type());

    // Calculate the scaling factor
    double scaleFactorX = (double)newWidth / image.cols;
    double scaleFactorY = (double)newHeight / image.rows;

    // Loop through the rows and columns of the resized image
    for (int y = 0; y < newHeight; y++) {
        for (int x = 0; x < newWidth; x++) {
            // Calculate the corresponding coordinates in the original image
            double xOriginal = x / scaleFactorX;
            double yOriginal = y / scaleFactorY;

            // Calculate the weights for the four nearest pixels
            double xWeight = xOriginal - floor(xOriginal);
            double yWeight = yOriginal - floor(yOriginal);
            double w1 = (1 - xWeight) * (1 - yWeight);
            double w2 = xWeight * (1 - yWeight);
            double w3 = (1 - xWeight) * yWeight;
            double w4 = xWeight * yWeight;

            // Get the pixel values of the four nearest pixels
            cv::Vec3b p1 = image.at<cv::Vec3b>(floor(yOriginal), floor(xOriginal));
            cv::Vec3b p2 = image.at<cv::Vec3b>(floor(yOriginal), ceil(xOriginal));
            cv::Vec3b p3 = image.at<cv::Vec3b>(ceil(yOriginal), floor(xOriginal));
            cv::Vec3b p4 = image.at<cv::Vec3b>(ceil(yOriginal), ceil(xOriginal));

            // Calculate the pixel value for the resized image using the weights
            cv::Vec3b pixel;
            for (int i = 0; i < 3; i++) {
                pixel[i] = (unsigned char)(w1 * p1[i] + w2 * p2[i] + w3 * p3[i] + w4 * p4[i]);
            }

            // Set the pixel value in the resized image
            resized.at<cv::Vec3b>(y, x) = pixel;
        }
    }

    // Return the resized image
    return resized;
}
