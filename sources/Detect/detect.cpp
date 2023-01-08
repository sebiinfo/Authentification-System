#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include "detect.hpp"

std::string path = "C:\\Users\\USER\\CLionProjects\\Authentification-System\\Authentification-System\\sources\\Detect\\haarcascades\\haarcascade_eye.xml";


// Function to adjust the threshold value
double adjustThreshold(cv::Mat image) {
    // Convert image to grayscale
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    // Calculate the mean intensity of the pixels in the image
    double meanIntensity = cv::mean(gray)[0];

    // Use a fixed value as the threshold adjustment
    double thresholdAdjustment = 10;

    // Return the adjusted threshold value
    return meanIntensity + thresholdAdjustment;
}


bool isEyeOpen(cv::Mat frame) {
    // Load the Haar cascade classifier for eye detection
    cv::CascadeClassifier eyeCascade;
    eyeCascade.load(path);

    // Detect eyes in the image using the Haar cascade classifier
    std::vector<cv::Rect> eyes;
        eyeCascade.detectMultiScale(frame, eyes, 1.1, 5, 0, cv::Size(20, 20));

    // Check if any eyes were detected
    if (eyes.size() > 0) {
        // Check if eye is open by analyzing the intensity of the pixels in the eye region
        cv::Mat eye = frame(eyes[0]);
        double threshold = adjustThreshold(eye);
        double meanIntensity = cv::mean(eye)[0];
        return meanIntensity > threshold;
    } else {
        return false;
    }
}


void normalizeIntensities(cv::Mat &image) {
    // Convert image to grayscale
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    // Compute mean and standard deviation of pixel intensities
    cv::Scalar mean, stddev;
    cv::meanStdDev(gray, mean, stddev);

    // Normalize the pixel intensities
    image = (image - mean[0]) / stddev[0];
}



bool detectEyes(cv::Mat image) {
    // Check if the image is empty
    if (image.empty()) {
        std::cout << "Invalid image" << std::endl;
        return false;
    }

    // Load the haar cascade for eye detection
    cv::CascadeClassifier eyeCascade;
    if (!eyeCascade.load(path)) {
        std::cout << "Failed to load eye cascade" << std::endl;
        return false;
    }

    // Detect eyes in the image
    std::vector<cv::Rect> eyes;
    eyeCascade.detectMultiScale(image, eyes, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

    // Return true if any eyes are detected, false otherwise
    return eyes.size() > 0;
}