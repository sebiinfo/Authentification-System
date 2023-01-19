#include "cascadecv.hpp"
#include "localizer.hpp"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <string>

Cascade_Localizer::Cascade_Localizer() : Cascade_Localizer(224, 224) {}

Cascade_Localizer::Cascade_Localizer(int w) : Cascade_Localizer(w, w) {}

Cascade_Localizer::Cascade_Localizer(int w,int h) : Localizer(w, h) {
    cascade.load("/usr/local/share/opencv4/haarcascades/haarcascade_frontalcatface.xml");
}

Cascade_Localizer::~Cascade_Localizer() {}

void Cascade_Localizer::localize_rect(cv::Mat & image, std::vector<cv::Rect> & faces) {
    cascade.detectMultiScale(image, faces, 1.1, 2, 0, cv::Size(30, 30));
}
