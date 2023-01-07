#include <opencv2/opencv.hpp>
#include "detect.hpp"


bool isEyeOpen(cv::Mat frame) {
    // Convert frame to grayscale
    cv::Mat gray;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

    // Use HoughCircles function to detect circles (i.e. eyes) in the image
    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1, gray.rows / 8, 100, 50, 0, 0);

    // Check if any circles (eyes) were detected
    if (circles.size() > 0) {
        // Check if eye is open by analyzing the intensity of the pixels in the circle (eye) region
        cv::Mat eye = gray(cv::Rect(circles[0][0] - circles[0][2], circles[0][1] - circles[0][2], circles[0][2] * 2, circles[0][2] * 2));
        double meanIntensity = cv::mean(eye)[0];
        return meanIntensity > 100;  // Threshold value may need to be adjusted
    } else {
        return false;
    }
}