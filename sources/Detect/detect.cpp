#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include "detect.hpp"

std::string path = "/haarcascade/haarcascade_eye.xml";


// Function to adjust the threshold value
double adjustThreshold(double meanIntensity) {
    // Use a value that is proportional to the mean intensity as the threshold adjustment
    double thresholdAdjustment = meanIntensity * 0.1;

    // Return the adjusted threshold value
    return 200 + thresholdAdjustment;
}

bool isEyeOpen(cv::Mat frame) {
    // Convert frame to grayscale
    cv::Mat gray;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    cv::CascadeClassifier eyeCascade;
    eyeCascade.load("haarcascade_eye.xml");

    // Detect eyes in the image using the Haar cascade classifier
    std::vector<cv::Rect> eyes;
    eyeCascade.detectMultiScale(gray, eyes, 1.1, 3, 0, cv::Size(30, 30));

    // Check if any eyes were detected
    if (eyes.size() > 0) {
        // Check if eye is open by analyzing the intensity of the pixels in the eye region
        cv::Mat eye = gray(eyes[0]);
        double meanIntensity = cv::mean(eye)[0];
        double threshold = adjustThreshold(meanIntensity);
        return meanIntensity > threshold;  // Threshold value may need to be adjusted
    } else {
        return false;
    }
}
