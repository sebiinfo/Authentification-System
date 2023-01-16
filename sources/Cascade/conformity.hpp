#include <iostream>
#include <vector>
#include "opencv2/opencv.hpp"
#include <opencv2/objdetect/objdetect.hpp>
#ifndef AUTHENTICATION_SYSTEM_CONFORMITY_H
#define AUTHENTICATION_SYSTEM_CONFORMITY_H


class Conformity {
public:
    Conformity();
    Conformity(std::vector<cv::Mat> input_faces);
    ~Conformity();
    void append_face(cv::Mat image);
    bool isEyeOpen(cv::Mat frame);
// Returns true if a face was detected, else false
    bool isFace(cv::Mat frame);
// Returns ture if an eye was detected, else false
    bool isEye(cv::Mat);
// Returns an array of cv::Rect corresponding to coordinates of faces recognized in the image
    std::vector<cv::Rect> detectFaces(cv::Mat image);
// Returns an array of cv::Rect corresponding to coordinates of eyes recognized in the image
    std::vector<cv::Rect> detectEyes(cv::Mat);
    bool openEyes(cv::Mat image);
//Returns an array containing only the conform images
    std::vector<cv::Mat> conformArray (std::vector<cv::Mat> faces);
// Returns the straightened face
    double get_angle_from_eyes(cv::Mat &image);
    cv::Mat rotate_face(cv::Mat &image, double angle);
// Checks if an image is comform ( face + open eyes )
    bool conform(cv::Mat image,bool smartcascade=true);
    // if smartcascade==true, we only take the images that are conform into the conformity vector faces.

    // Gets the ith element of the vector faces
    cv::Mat get_face(int i);
    void normalizeIntensities(cv::Mat &image);


private:
std::vector <cv::Mat> faces;
};


#endif //AUTHENTICATION_SYSTEM_CONFORMITY_H
