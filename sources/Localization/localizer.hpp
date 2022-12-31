#ifndef AUTHENTICATION_SYSTEM_LOCALIZER_HPP
#define AUTHENTICATION_SYSTEM_LOCALIZER_HPP

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/core/mat.hpp>
#include <cassert>

class Localizer{
  public:
    Localizer() {};
    ~Localizer() {};
    virtual std::vector<cv::Rect> localize_rect(cv::Mat & image) {assert(false);};
    virtual std::vector<cv::Mat> localize(cv::Mat & image) {assert(false)};
};

#endif