#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include "detect.hpp"
#include <vector>

std::string path_face = "C:\\Users\\USER\\CLionProjects\\Authentification-System\\Authentification-System\\sources\\Detect\\haarcascades\\haarcascade_eye.xml";
std::string path_eye = "C:\\Users\\USER\\CLionProjects\\Authentification-System\\Authentification-System\\sources\\Detect\\haarcascades\\haarcascade_eye.xml";
double pi=3.14159265358979323846;

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
        std::cout << "Failed to load the face cascade at directory:" << path_face << std::endl;
     }

    std::vector<cv::Rect> faces;
    faceCascade.detectMultiScale(image,faces,1.06, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

    return faces;
}

std::vector<cv::Rect> detectEyes(cv::Mat image) {
    cv::CascadeClassifier faceCascade;
    if (!faceCascade.load(path_eye)){
        std::cout << "Failed to load the face cascade:" << path_face << std::endl;
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

cv::Mat rotate_face(cv::Mat &image){

    //Load cascades
    cv::CascadeClassifier face_cascade;
    if (!face_cascade.load(path_face)){
        std::cout<<"Failed to load the face cascade: "<<path_face<<std::endl;
    }
    cv::CascadeClassifier eye_cascade;
    if (!eye_cascade.load(path_eye)){
        std::cout<<"Failed to load the eye cascade: "<<path_face<<std::endl;
}
    while (1) {
        //Convert to grayscale
        cv::Mat gray;
        cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
        std::vector<cv::Rect> faces;
        face_cascade.detectMultiScale(gray, faces, 1.1, 5);
        int x, y, w, h;
        for (int i = 0; i < faces.size(); i++) {
            x = faces[i].x;
            y = faces[i].y;
            w = faces[i].width;
            h = faces[i].height;
            cv::rectangle(image, cv::Point(x, y), cv::Point(x + w, y + h), cv::Scalar(0, 255, 0), 2);
            cv::circle(image, cv::Point(x + int(w * 0.5), y + int(h * 0.5)), 4, cv::Scalar(0, 255, 0), -1);
        }
        std::vector<cv::Rect> eyes;
        eye_cascade.detectMultiScale(gray(cv::Rect(x, y, w, h)), eyes, 1.1, 4);
        int index = 0;
        cv::Rect eye_1(0, 0, 0, 0);
        cv::Rect eye_2(0, 0, 0, 0);
        for (int i = 0; i < eyes.size(); i++) {
            if (index == 0) {
                eye_1 = eyes[i];
            } else if (index == 1) {
                eye_2 = eyes[i];
            }
            cv::rectangle(image(cv::Rect(x, y, w, h)), cv::Point(eyes[i].x, eyes[i].y),
                          cv::Point(eyes[i].x + eyes[i].width, eyes[i].y + eyes[i].height), cv::Scalar(0, 0, 255), 2);
            index++;
        }
        if (eye_1.x != 0 && eye_2.x != 0) {
            cv::Rect left_eye;
            cv::Rect right_eye;
            if (eye_1.x < eye_2.x) {
                left_eye = eye_1;
                right_eye = eye_2;
            } else {
                left_eye = eye_2;
                right_eye = eye_1;
            }
            cv::Point left_eye_center = cv::Point(left_eye.x + (left_eye.width / 2),
                                                  left_eye.y + (left_eye.height / 2));
            cv::Point right_eye_center = cv::Point(right_eye.x + (right_eye.width / 2),
                                                   right_eye.y + (right_eye.height / 2));
            double left_eye_x=left_eye_center.x;
            double left_eye_y=left_eye_center.y;
            double right_eye_x=right_eye_center.x;
            double right_eye_y=right_eye_center.y;
            double delta_x, delta_y;
            delta_x=right_eye_x-left_eye_x;
            delta_y=right_eye_y-left_eye_y;
            double angle_rad = std::atan(delta_y/delta_x);
            double angle = (angle_rad*180)/pi;
            if (angle>10)
            { // If a right tilt is detected
                //Rotate face left
                return rotate_face_aux(image, angle);
            }
            else if (angle<10)
            { //If a left tilt is detected
                //Rotate face right
                return rotate_face_aux(image, angle);
            }
            else{return image;}
        }
    }
}

cv::Mat rotate_face_aux(cv::Mat &image, double angle){
//    cv::Size s= image.size();
//    double height =s.height;
//    double width = s.width;
    int height, width;

    height = image.rows;
    width = image.cols;

    cv::Point image_center = cv::Point(height/2,width/2);
    cv::Mat rotation_mat=cv::getRotationMatrix2D(image_center, angle, 1);

    double abs_cos = abs(cos(angle));
    double abs_sin = abs(sin(angle));
    int bound_w = height * abs_sin + width * abs_cos;
    int bound_h = height * abs_cos + width * abs_sin;

    rotation_mat.at<double>(0,2) += bound_w/2 - image_center.x;
    rotation_mat.at<double>(1,2) += bound_h/2 - image_center.y;

    cv::Mat rotated_mat;
    cv::warpAffine(image, rotated_mat,rotation_mat, cv::Size(bound_w, bound_h));

    return rotated_mat;
}
