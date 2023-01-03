#include "vectorizer.hpp"
#include <cassert>
#include <opencv2/core.hpp>

Vectorizer::Vectorizer(int num_people, int num_feature) {
    this->num_people = num_people;
    this->num_feature = num_feature;
}

Vectorizer::~Vectorizer() {}

void Vectorizer::train(std::vector<cv::Mat> train_images, std::vector<int> train_label) {
    assert(false);
}

cv::Mat Vectorizer::vectorize(cv::Mat &image) { 
    assert(false);
    return cv::Mat(); 
}
