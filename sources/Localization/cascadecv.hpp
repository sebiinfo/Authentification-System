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

    void localize_rect(cv::Mat & image, std::vector<cv::Rect> faces);

  private:
    cv::CascadeClassifier cascade;
};

#endif // AUTHENTICATION_SYSTEM_CASCADE_CV_HPP
