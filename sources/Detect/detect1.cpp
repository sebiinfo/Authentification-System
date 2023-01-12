#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include "detect.hpp"
#include <vector>

#define YASSINE 0 // set to 1 to load local path for yassine

#if YASSINE == 1
std::string path_face = "C:\\Users\\USER\\CLionProjects\\Authentification-System\\Authentification-System\\sources\\Detect\\haarcascades\\haarcascade_eye.xml";
std::string path_eye = "C:\\Users\\USER\\CLionProjects\\Authentification-System\\Authentification-System\\sources\\Detect\\haarcascades\\haarcascade_eye.xml";

#else

std::string path_face = "/Users/florencepoggi/Documents/Romain/Education/Bachelor X/Courses/Semester 3/CSE 201 - CPP/Project/Authentification-System/sources/Detect/haarcascades/haarcascade_frontalface_default.xml";
std::string path_eye = "/Users/florencepoggi/Documents/Romain/Education/Bachelor X/Courses/Semester 3/CSE 201 - CPP/Project/Authentification-System/sources/Detect/haarcascades/haarcascade_eye.xml";

#endif



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
return eyes.size()>0;
}

bool isFace(cv::Mat image){

    int dim_face = 60;
    std::vector<cv::Rect> faces = detectFaces(image,dim_face);
    return faces.size() > 0;
}


bool isEye(cv::Mat image) {
    std::vector<cv::Rect> eyes = detectEyes(image,30);
    return eyes.size() > 0;
}

std::vector<cv::Rect> detectFaces(cv::Mat image,int dim) {
    cv::CascadeClassifier faceCascade;
    if (!faceCascade.load(path_face)){
        std::cout << "Failed to laod the faca cascade at directory:" << path_face << std::endl;
     }

    std::vector<cv::Rect> faces;
    std::cout << dim << std::endl;

    faceCascade.detectMultiScale(image,faces,1.06, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(dim, dim));

    return faces;
}

std::vector<cv::Rect> detectEyes(cv::Mat image, int dim) {
    dim = 60;
    cv::CascadeClassifier faceCascade;
    if (!faceCascade.load(path_eye)){
        std::cout << "Failed to laod the faca cascade at directory:" << path_face << std::endl;
     }

    std::vector<cv::Rect> faces;
    faceCascade.detectMultiScale(image,faces,1.06, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(dim, dim));

    return faces;
}

bool conform(cv::Mat image)
{
    if( !isFace(image) ) {
        std::cout << "No face was found";
        return false;
    }
    if (isEyeOpen(image)) {
        std::cout << "Face and eyes are open";
        return true;
    }
    std::cout << "Face was found but eyes were closed";
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
