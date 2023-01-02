#include "model.hpp"
#include "localizer.hpp"
#include "vectorizer.hpp"
#include "classifier.hpp"
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <string>
#include <cassert>

Model::Model(int num_people, int num_feature, int width, int height,
             std::string localizer, std::string vectorizer, std::string classifier) {
    this->num_people = num_people;
    this->num_feature = num_feature;
    this->width = width;
    this->height = height;
    
}

Model::~Model() {}

void Model::predict(cv::Mat image, std::vector<cv::Rect>* faces, std::vector<int>* ids) {
    std::vector<cv::Mat> numerical_reps;

    localizer.localize_update(image, faces); // hopefully this loads up faces with faces :)
    vectorizer.vectorize_update(image, faces[i], numerical_reps);
    for (int i = 0; i < faces.size(); i ++) {ids.push_back(classifier.classify(numerical_reps[i]));}
}

std::vector<int> Model::predict(cv::Mat image) {
    std::vector<cv::Rect> faces;
    std::vector<int> ids;
    predict(image, faces, ids);
    return ids;
}
