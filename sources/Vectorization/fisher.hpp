#ifndef AUTHENTICATION_SYSTEM_FISHER_HPP
#define AUTHENTICATION_SYSTEM_FISHER_HPP

#endif // AUTHENTICATION_SYSTEM_FISHER_HPP

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/core/mat.hpp>

class Fisher {
  public:
    Fisher();
    ~Fisher();
    int predict(cv::Mat);

  private:
    cv::Mat normalize(cv::InputArray);
    void train();
    std::vector<cv::Mat> images;
    std::vector<int> labels;
};
