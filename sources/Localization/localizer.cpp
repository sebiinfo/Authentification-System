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

std::vector<cv::Mat> Localizer::Transform(cv::Mat image,std::vector<cv::Rect> faces)
{
    assert(false);
}


double get_angle_from_eyes(cv::Mat image, std::vector<cv::Rect> &faces){
    assert(false);
}

cv::Mat Localizer::rotate_face(cv::Mat image, std::vector<cv::Rect> &faces, double angle)
{
    //    cv::Size s= image.size();
    //    double height =s.height;
    //    double width = s.width;

	assert(false);
//    if(-10<angle<10){
//        return image;
//    }
//    int height, width;
//    height = image.rows;
//    width = image.cols;

//    cv::Point2f image_center = cv::Point(height / 2, width / 2);
//    cv::Mat rotation_mat = cv::getRotationMatrix2D(image_center, angle, 1);

//    double abs_cos = abs(cos(angle));
//    double abs_sin = abs(sin(angle));
//    int bound_w = height * abs_sin + width * abs_cos;
//    int bound_h = height * abs_cos + width * abs_sin;

//    rotation_mat.at<double>(0, 2) += bound_w / 2 - image_center.x;
//    rotation_mat.at<double>(1, 2) += bound_h / 2 - image_center.y;

//    cv::Mat rotated_mat;
//    cv::warpAffine(image, image, rotation_mat, cv::Size(bound_w, bound_h));
//    return image;

}
