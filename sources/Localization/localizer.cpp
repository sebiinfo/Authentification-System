#include "localizer.hpp"
#include "../Cascade/cascade_Base.hpp"
#include "../Cascade/cascade_detect_cv.hpp"
#include <opencv2/core/mat.hpp>


Localizer::Localizer() : Localizer(244,10) {}

Localizer::Localizer(int w) : Localizer(w,10) {}

Localizer::Localizer(int w,int pad): Localizer(w,w,pad) {}

Localizer::Localizer(int w, int h,int pad)
{
    width = w;
    height = h;
    padding = pad;
}

Localizer::~Localizer() {}


void Localizer::localize_rect(cv::Mat & image, std::vector<cv::Rect> & faces)
{
    assert(false);
}

std::vector<cv::Rect> Localizer::localize_rect(cv::Mat & image) 
{
    assert(false);
}

std::vector<cv::Mat> Localizer::localize(cv::Mat &image, std::vector<cv::Rect> & faces_rect) 
{
    assert(false);
}

std::vector<cv::Mat> Localizer::localize(cv::Mat & image) 
{
    assert(false);
}

std::vector<cv::Mat> Localizer::Transform(cv::Mat image)
{
    assert(false);
}


double get_angle_from_eyes(std::vector<cv::Rect> eyes){
    assert(false);
}

void Localizer::rotate_face(cv::Mat &image, double angle)
{

	assert(false);
}
