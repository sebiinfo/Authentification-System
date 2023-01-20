#include <iostream>
#include <vector>
//#include "opencv2/opencv.hpp"
#include "cascade_detect_cv.hpp"
#include <opencv2/objdetect/objdetect.hpp>
#include "cascade_Base.hpp"
#ifndef AUTHENTICATION_SYSTEM_CONFORMITY_H
#define AUTHENTICATION_SYSTEM_CONFORMITY_H


class Cascade_conformity: public cascade_Base{
public:
    Cascade_conformity();
    Cascade_conformity(std::vector<cv::Rect> &input_faces);
    ~Cascade_conformity();
    void load_cascade_face(std::string path_f);
    void load_cascade_eyes(std::string path_e);
    // Returns an array of cv::Mat corresponding to coordinates of faces recognized in the image
    std::vector<cv::Rect> detectFaces(cv::Mat &image);
    // Returns an array of cv::Mat corresponding to coordinates of eyes recognized in the image
    std::vector<cv::Rect> detectEyes(cv::Mat image);
    // Returns ture if an eye was detected, else false
    bool isFace(cv::Mat image, std::vector<cv::Rect> &faces);
    void isEye(cv::Mat image, std::vector<cv::Rect> &faces);
    cv::Mat convert_rect_to_mat(cv::Rect &rect);
    // gets the ith face
    cv::Rect get_face(int i);
    // Normalize Intensities of the pixels (efficiency to be tested)
    void normalizeIntensities(cv::Mat &image);
    void detectMultiScale(cv::Mat image, std::vector<cv::Rect> &faces, double scaleFactor, double minNeighbors, double flags, cv::Size minSize);

private:



	cv::CascadeClassifier cascade_face;
	cv::CascadeClassifier cascade_eyes;
};


#endif //AUTHENTICATION_SYSTEM_CONFORMITY_H
