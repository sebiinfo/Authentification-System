#ifndef AUTHENTICATION_SYSTEM_FISHER_HPP
#define AUTHENTICATION_SYSTEM_FISHER_HPP

#include "Vectorizer.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/core/mat.hpp>

class Fisher : public Vectorizer {
  public:
    Fisher();
    Fisher(int num_people, int num_feature);
    ~Fisher();

  private:
    cv::Mat normalize(cv::InputArray);
    std::vector<cv::Mat> images = std::vector<cv::Mat>();
    std::vector<int> labels = std::vector<int>();
    void train(std::vector<cv::Mat> &images, std::vector<int> &labels);
    int num_components;
};
#endif // AUTHENTICATION_SYSTEM_FISHER_HPP
