#include "localizer.hpp"
#include <opencv2/core/mat.hpp>


Localizer::Localizer()
{
    width = 224;
    height = 224;
    padding = 10;
}

Localizer::Localizer(int w,int pad)
{
    width = w;
    height = w;
    padding = pad;
}

Localizer::Localizer(int w, int h,int pad){
    width = w;
    height = h;
    padding = pad;
}

Localizer::~Localizer() {}


void Localizer::localize_rect(cv::Mat & image, std::vector<cv::Rect> & faces)
{
    assert(false);
}

std::vector<cv::Rect> Localizer::localize_rect(cv::Mat & image) {
    assert(false);
}

std::vector<cv::Mat> Localizer::localize(cv::Mat &image, std::vector<cv::Rect> & faces_rect) {
    assert(false);
}

std::vector<cv::Mat> Localizer::localize(cv::Mat & image) {
    assert(false);
}

