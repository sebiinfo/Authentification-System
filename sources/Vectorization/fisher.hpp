#ifndef AUTHENTICATION_SYSTEM_FISHER_HPP
#define AUTHENTICATION_SYSTEM_FISHER_HPP

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "vectorizer.hpp"
#include <opencv2/core/mat.hpp>

class Fisher : public Vectorizer {
  public:
    Fisher(int num_people, int num_feature);
    ~Fisher();
    cv::Mat vectorize(cv::Mat &image);

  private:
    cv::Mat normalize(cv::InputArray &src);
    void load_images();
    std::vector<cv::Mat> images = std::vector<cv::Mat>();
    std::vector<int> labels = std::vector<int>();
    cv::PCA pca;
    cv::LDA lda;
    int num_components;
    int dim;
};
#endif // AUTHENTICATION_SYSTEM_FISHER_HPP
