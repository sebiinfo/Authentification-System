#include "Vectorizer.hpp"
#include <cassert>
#include <opencv2/core.hpp>

Vectorizer::Vectorizer(int num_people, int num_feature) {
    this->num_people = num_people;
    this->num_feature = num_feature;
}

Vectorizer::~Vectorizer() {}

virtual std::array<float> Vectorizer::vectorize(cv::Mat image, std::vector<cv::Rect> faces) {assert(false, "Not implemented");}
virtual std::array<float> Vectorizer::vectorize(cv::Mat image) {assert(false, "Not implemented");}
virtual void Vectorizer::vectorize_update(cv::Mat image, std::vector<cv::Rect> faces, std::vector<std::vector<float>> numerical_reps) {assert(false, "Not implemented");}
virtual void Vectorizer::vectorize_update(cv::Mat image, std::vector<std::vector<float>> numerical_reps) {assert(false, "Not implemented");}

