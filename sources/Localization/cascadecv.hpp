#ifndef AUTHENTICATION_SYSTEM_CASCADE_CV_HPP
#define AUTHENTICATION_SYSTEM_CASCADE_CV_HPP

#include "localizer.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/core/mat.hpp>
#include <opencv2/objdetect.hpp>

class Cascade_Detector_CV : public Localizer {
  public:
    Cascade_Detector_CV();
    Cascade_Detector_CV(int h);
    Cascade_Detector_CV(int w, int h);
    ~Cascade_Detector_CV();

    std::vector<cv::Rect> localize_rect(cv::Mat &image);
    std::vector<cv::Mat> localize(cv::Mat &image);

  private:
    cv::CascadeClassifier cascade;
    int width;
    int height;
};

#endif // AUTHENTICATION_SYSTEM_CASCADE_CV_HPP
