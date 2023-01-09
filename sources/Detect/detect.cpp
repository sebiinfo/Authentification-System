#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include "detect.hpp"
#include <vector>

std::string path_face = "/Authentification-System/sources/Detect/haarcascades/haarcascade_frontalface.xml";
std::string path_eye = "/Authentification-System/sources/Detect/haarcascades/haarcascade_eye.xml";

// Function to adjust the threshold value
double adjustThreshold(cv::Mat image) {
    // Convert image to grayscale
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    // Calculate the mean intensity of the pixels in the image
    double meanIntensity = cv::mean(gray)[0];

    // Use a fixed value as the threshold adjustment
    double thresholdAdjustment = 0;

    // Return the adjusted threshold value
    return meanIntensity + thresholdAdjustment;
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


bool isEyeOpen(cv::Mat frame) {
    // Load the Haar cascade classifier for eye detection
    cv::CascadeClassifier eyeCascade;
    eyeCascade.load(path_face);

    // Detect eyes in the image using the Haar cascade classifier
    std::vector<cv::Rect> eyes;
    eyeCascade.detectMultiScale(frame, eyes, 1.06, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

    // Check if any eyes were detected
    if (eyes.size() > 0) {
        // Check if eye is open by analyzing the intensity of the pixels in the eye region
        cv::Mat eye = frame(eyes[0]);
        double threshold = adjustThreshold(eye);
        double meanIntensity = cv::mean(eye)[0];
        return meanIntensity > 20;
    } else {
        return false;
    }
}

bool isFace(cv::Mat image){
    std::vector<cv::Rect> faces = detectFaces(image);
    return faces.size() > 0;
}


bool isEye(cv::Mat image) {
    std::vector<cv::Rect> eyes = detectEyes(image);
    return eyes.size() > 0;
}

std::vector<cv::Rect> detectFaces(cv::Mat image) {
    cv::CascadeClassifier faceCascade;
    if (!faceCascade.load(path_face)){
        std::cout << "Failed to laod the faca cascade at directory:" << path_face << std::endl;
     }

    std::vector<cv::Rect> faces;
    faceCascade.detectMultiScale(image,faces,1.06, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

    return faces;
}

std::vector<cv::Rect> detectEyes(cv::Mat image) {
    cv::CascadeClassifier faceCascade;
    if (!faceCascade.load(path_eye)){
        std::cout << "Failed to laod the faca cascade at directory:" << path_face << std::endl;
     }

    std::vector<cv::Rect> faces;
    faceCascade.detectMultiScale(image,faces,1.06, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

    return faces;
}

bool conform(cv::Mat image)
{
    if( !isFace(image) ) {
//        std::cout << "No face was found";
        return false;
    }
    if (isEyeOpen(image)) {
//        std::cout << "Face and eyes are open";
        return true;
    }
//    std::cout << "Face was found but eyes were closed";
    return false;
}

std::vector<cv::Mat> conformArray (std::vector<cv::Mat> faces)
{
    std::vector<cv::Mat> conformArray;
    for (int i =0; i<faces.size();i++){
        if (conform(faces[i])){
            conformArray.push_back(faces[i]);
        }
    }
    return conformArray;
}
