#include "cascadecv.hpp"
#include "localizer.hpp"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <string>

Cascade_Detector_CV::Cascade_Detector_CV() : Cascade_Detector_CV(224, 224) {}

Cascade_Detector_CV::Cascade_Detector_CV(int h) : Cascade_Detector_CV(h, 224) {}

Cascade_Detector_CV::Cascade_Detector_CV(int w, int h) : Localizer() {
    cascade.load(
        "/usr/local/share/opencv4/haarcascades/haarcascade_frontalcatface.xml");
    this->width = w;
    this->height = h;
}

Cascade_Detector_CV::~Cascade_Detector_CV() {}

std::vector<cv::Rect> Cascade_Detector_CV::localize_rect(cv::Mat &image) {
    std::vector<cv::Rect> faces;
    cascade.CascadeClassifier::detectMultiScale(image, faces, 1.1, 2, 0,
                                                cv::Size(30, 30));
    return faces;
}

std::vector<cv::Mat> Cascade_Detector_CV::localize(cv::Mat &image) {
    std::vector<cv::Rect> faces_rect =
        Cascade_Detector_CV::localize_rect(image);
    std::vector<cv::Mat> faces;
    for (int i = 0; i < faces_rect.size(); i++) {
        cv::Mat temp;
        cv::resize(cv::Mat(image, faces_rect[i]), temp, cv::Size(width, height),
                   0, 0, cv::INTER_LINEAR);
        faces.push_back(temp);
    }
    return faces;
}
