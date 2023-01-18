#include "cascadecv.hpp"
#include "localizer.hpp"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <string>

Cascade_Detector_CV::Cascade_Detector_CV() : Cascade_Detector_CV(224, 224) {}

Cascade_Detector_CV::Cascade_Detector_CV(int w) : Cascade_Detector_CV(w, w) {}

Cascade_Detector_CV::Cascade_Detector_CV(int w, int h) : Localizer(w, h) {
    cascade.load(
        "/usr/local/share/opencv4/haarcascades/haarcascade_frontalcatface.xml");
}

Cascade_Detector_CV::~Cascade_Detector_CV() {}

void Cascade_Detector_CV::localize_rect(cv::Mat &image,
                                        std::vector<cv::Rect> &faces) {
    cascade.detectMultiScale(image, faces, 1.1, 2, 0, cv::Size(30, 30));
}
