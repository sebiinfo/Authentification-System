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

    void localize_rect(cv::Mat & image, std::vector<cv::Rect> faces);

  private:
    cv::CascadeClassifier cascade;
};

#endif // AUTHENTICATION_SYSTEM_CASCADE_CV_HPP
