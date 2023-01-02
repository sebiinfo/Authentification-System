#ifndef AUTHENTICATION_SYSTEM_LOCALIZER_HPP
#define AUTHENTICATION_SYSTEM_LOCALIZER_HPP

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/core/mat.hpp>
#include <cassert>

class Localizer{
  public:
    Localizer();
    Localizer(int w);
    Localizer(int w, int h);
    ~Localizer();

    virtual void localize_rect(cv::Mat & image, std::vector<cv::Rect> & faces);
    std::vector<cv::Rect> localize_rect(cv::Mat & image);
    std::vector<cv::Mat> localize(cv::Mat & image, std::vector<cv::Rect> & faces_rect);
    std::vector<cv::Mat> localize(cv::Mat & image);
    
  private:
    int width;
    int height;
};

#endif