#ifndef AUTHENTICATION_SYSTEM_VECTORIZER_HPP
#define AUTHENTICATION_SYSTEM_VECTORIZER_HPP

#include <opencv2/core.hpp>

class Vectorizer {
    /*
    A base class for different vectorization methods that would be implement
    */
  public:
    Vectorizer(int num_people, int num_feature, std::vector<cv::Mat> &images,
               std::vector<int> &labels);
    Vectorizer(int num_people, int num_feature);
    ~Vectorizer();

    virtual void train(std::vector<cv::Mat> train_images, std::vector<int> train_labels);
    virtual cv::Mat vectorize(cv::Mat &image);

    int num_people;
    int num_feature;
};

#endif // AUTHENTICATION_SYSTEM_VECTORIZER_HPP
