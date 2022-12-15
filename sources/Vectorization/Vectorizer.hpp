#ifndef AUTHENTICATION_SYSTEM_VECTORIZER_HPP
#define AUTHENTICATION_SYSTEM_VECTORIZER_HPP

#endif // AUTHENTICATION_SYSTEM_VECTORIZER_HPP

#include <opencv2/core.hpp>

class Vectorizer {
    /*
    A base class for different vectorization methods that would be implement
    */
public:
    Vectorizer(int num_people, int num_feature);
    ~Vectorizer();

    virtual std::array<float> vectorize(cv::Mat image, std::vector<cv::Rect> faces);
    virtual std::array<float> vectorize(cv::Mat image);
    virtual void vectorize_update(cv::Mat image, std::vector<cv::Rect> faces, std::vector<std::vector<float>> numerical_reps);
    virtual void vectorize_update(cv::Mat image, std::vector<std::vector<float>> numerical_reps);

    int num_people;
    int num_feature;

};