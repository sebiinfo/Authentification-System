#include "localizer.hpp"
//#include "opencv2/core.hpp"
//#include "opencv2/highgui.hpp"
//#include "opencv2/imgproc.hpp"
#include <opencv2/core/mat.hpp>
#include <cassert>
#include "../Detect/detect.hpp"

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

void Localizer::localize_rect(cv::Mat & image, std::vector<cv::Rect> & faces) {assert(false);}

std::vector<cv::Rect> Localizer::localize_rect(cv::Mat & image) {
    std::vector<cv::Rect> faces;
    localize_rect(image, faces);
    return faces;
}

std::vector<cv::Mat> Localizer::localize(cv::Mat & image, std::vector<cv::Rect> & faces_rect) {
    localize_rect(image, faces_rect);
    std::vector<cv::Mat> faces;
    for (int i = 0; i < faces_rect.size(); i++) {
        cv::Mat temp;
        Resize(cv::Mat(image, faces_rect[i]), temp, cv::Size(width, height), 0, 0, cv::INTER_LINEAR)
        faces.push_back(temp);
    }
    return faces;
}

std::vector<cv::Mat> Localizer::localize(cv::Mat & image) {
    std::vector<cv::Rect> faces_rect;
    return localize(image, faces_rect);
}


