#include "cascadecv.hpp"
#include "localizer.cpp"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <string>

Cascade_Detector_CV::Cascade_Detector_CV() : Localizer() {
    cascade.load("/usr/local/share/opencv4/haarcascades/haarcascade_frontalcatface.xml");
}

Cascade_Detector_CV::Cascade_Detector_CV(h) : Localizer() {
    cascade.load("/usr/local/share/opencv4/haarcascades/haarcascade_frontalcatface.xml");
    this->w = h; this->h = h;
}

Cascade_Detector_CV::Cascade_Detector_CV(w, h) : Localizer() {
    cascade.load("/usr/local/share/opencv4/haarcascades/haarcascade_frontalcatface.xml");
    this->w = w; this->h = h;
}

Cascade_Detector_CV::~Cascade_Detector_CV() {}

std::vector<cv::Rect> Cascade_Detector_CV::localize_rect(cv::Mat & image) {
    std::vector<Rect> faces;
    cascade.detechMultiScale(image, faces, 1.1, 2, 0, Size(30, 30));
    return faces;
}

std::vector<cv::Mat> Cascade_Detector_CV::localize(cv::Mat & image) {
    std::vector<cv::Rect> faces_rect = Cascade_Detector_CV::localize_rect();
    std::vector<cv::Mat> faces;
    for (int i = 0; i < faces_rect.size(); i++) {
        cv::Mat temp;
        cv::Resize(cv::Mat(img, faces_rect[i]), temp, cv::Size(w, h), 0, 0, cv::INTER_LINEAR)
        faces.push_back(temp);
    }
    return faces;
}