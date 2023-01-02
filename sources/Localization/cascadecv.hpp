#ifndef AUTHENTICATION_SYSTEM_CASCADE_CV_HPP
#define AUTHENTICATION_SYSTEM_CASCADE_CV_HPP

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "localizer.hpp"
#include <opencv2/core/mat.hpp>

class Cascade_Detector_CV : public Localizer {
  public:
    Cascade_Detector_CV();
    Cascade_Detector_CV(h);
    Cascade_Detector_CV(w, h);
    ~Cascade_Detector_CV();

    std::vector<cv::Rect> localize_rect(cv::Mat & image);
    std::vector<cv::Mat> localize(cv::Mat & image);

  private:
    cv::CascadeClassifier cascade;
    int w = 224;
    int h = 224;
};

#endif // AUTHENTICATION_SYSTEM_CASCADE_CV_HPP
