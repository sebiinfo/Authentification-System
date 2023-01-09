#include "localizer.hpp"
#include <opencv2/core/mat.hpp>
#include "../Detect/detect.hpp"
#include "../Cropimage/cropimage.hpp"
#include "../Rescale/rescale.hpp"

Localizer::Localizer()
{
    width = 224;
    height = 224;
}

Localizer::Localizer(int w)
{
    width = w;
    height = w;
}

Localizer::Localizer(int w, int h)
{
    width = w;
    height = h;
}

Localizer::~Localizer() {}


void Localizer::localize_rect(cv::Mat & image, std::vector<cv::Rect> & faces)
{
    faces = detectFaces(image);
}

std::vector<cv::Rect> Localizer::localize_rect(cv::Mat & image) {
    std::vector<cv::Rect> faces;
    localize_rect(image, faces);
    return faces;
}

std::vector<cv::Mat> Localizer::localize(cv::Mat & image, std::vector<cv::Rect> & faces_rect) {
    localize_rect(image, faces_rect);
    std::vector<cv::Mat> faces;
    faces = cropArray(image,faces_rect);
    faces = rescaleArray(faces,width,height);
    return faces;
}

std::vector<cv::Mat> Localizer::localize(cv::Mat & image) {
    std::vector<cv::Rect> faces_rect;
    return localize(image, faces_rect);
}

