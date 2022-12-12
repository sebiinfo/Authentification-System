#include "model.hpp"
#include "Facedata.hpp"
#include <opencv2/core.hpp>


Model::Model(int num_people, int num_feature, int localizer, int vectorizer, int classifier, std::vector<Facedata>* data) {
    this->num_people = num_people;
    this->num_feature = num_feature;
    this->localizer = localizer;
    this->vectorizer = vectorizer(num_people, num_feature, data);
    this->classifier = classifier(num_people, num_feature, data);
}

Model::Model(int num_people, int num_feature, std::vector<Facedata>* data) {
    this->num_people = num_people;
    this->num_feature = num_feature;
    this->localizer = 0;
    this->vectorizer = 0;
    this->classifier = 0;
}

Model::~Model() {}

void Model::predict(cv::Mat image, std::vector<cv::Rect>* faces, std::vector<int>* ids) {
    std::vector<std::vector<float>> numerical_reps;

    localizer.localize_update(image, faces); // hopefully this loads up faces with faces :)
    vectorizer.vectorize_update(image, faces[i], numerical_reps);
    for (int i = 0; i < faces.size(); i ++) {ids.push_back(classifier.classify(numerical_reps[i]));}
}

std::vector<int> Model::predict(cv::Mat image) {
    std::vector<cv::Rect> faces;
    std::vector<int> ids;
    forward(image, faces, ids);
    return ids;
}
