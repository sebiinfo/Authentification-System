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
    cv::Mat vectorize(const cv::Mat &image);
    int predict_label(const cv::Mat &projection);
    cv::PCA pca;
    cv::LDA lda;

  private:
    cv::Mat normalize(cv::InputArray &src);
    void vectorize_trainset();
    void load_images();
    std::vector<cv::Mat> images;
    std::vector<int> labels;
    cv::Mat vectorized_images;
    int num_components;
    int dim;
};
#endif // AUTHENTICATION_SYSTEM_FISHER_HPP
