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

Cascade_Detector_CV::Cascade_Detector_CV(w) : Localizer(w) {
    cascade.load("/usr/local/share/opencv4/haarcascades/haarcascade_frontalcatface.xml");
}

Cascade_Detector_CV::Cascade_Detector_CV(w, h) : Localizer(w, h) {
    cascade.load("/usr/local/share/opencv4/haarcascades/haarcascade_frontalcatface.xml");
}

Cascade_Detector_CV::~Cascade_Detector_CV() {}

void Cascade_Detector_CV::localize_rect(cv::Mat & image, std::vector<cv::Rect> & faces) {
    cascade.detechMultiScale(image, faces, 1.1, 2, 0, Size(30, 30));
}
