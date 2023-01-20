#ifndef AUTHENTICATION_SYSTEM_CASCADE_CV_HPP
#define AUTHENTICATION_SYSTEM_CASCADE_CV_HPP

#include "localizer.hpp"
#include <opencv2/core/mat.hpp>
#include <opencv2/objdetect.hpp>
#include "../Cascade/cascade_Base.hpp"

class Cascade_Localizer : public Localizer {
  public:
    Cascade_Localizer();
    Cascade_Localizer(int w);
    Cascade_Localizer(int w, int pad);
    Cascade_Localizer(int w, int h, int pad);
    ~Cascade_Localizer();

    void localize_rect(cv::Mat & image, std::vector<cv::Rect> & faces);
    bool is_pad(cv::Mat image, cv::Rect face);

    std::vector<cv::Mat> Crop(cv::Mat image,std::vector<cv::Rect> faces);
    void Rescale(std::vector<cv::Mat> &images);

    std::vector<cv::Mat> Transform(cv::Mat image,std::vector<cv::Rect> faces);

    cascade_Base cascade;
  private:
    void Crop_(cv::Mat &image,cv::Rect face);
    void Rescale(cv::Mat &image);




};

#endif // AUTHENTICATION_SYSTEM_CASCADE_CV_HPP
