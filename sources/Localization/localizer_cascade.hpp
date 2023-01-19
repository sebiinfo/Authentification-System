#ifndef AUTHENTICATION_SYSTEM_CASCADE_CV_HPP
#define AUTHENTICATION_SYSTEM_CASCADE_CV_HPP

#include "localizer.hpp"
#include <opencv2/core/mat.hpp>
#include <opencv2/objdetect.hpp>

class Cascade_Localizer : public Localizer {
  public:
    Cascade_Localizer();
    Cascade_Localizer(int h);
    Cascade_Localizer(int w, int h);
    ~Cascade_Localizer();

    void localize_rect(cv::Mat & image, std::vector<cv::Rect> & faces);

  private:
    cv::CascadeClassifier cascade;
};

#endif // AUTHENTICATION_SYSTEM_CASCADE_CV_HPP
