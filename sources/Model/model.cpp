#include "model.hpp"
#include <opencv2/core.hpp>

Model::Model(int num_people; int localizer, int detector, int classifier, int num_feature, FacialData* data) {
    this->num_people = num_people;
    this->localizer = localizer;
    this->detector = detector;
    this->classifier = classifier;
    this->num_feature = num_feature;
    this->data = data;
}

Model::Model(int num_feature, FacialData* data) {
    this->num_people = num_people;
    this->localizer = 0;
    this->detector = 0;
    this->classifier = 0;
    this->num_feature = num_feature;
    this->data = data;
}

Model::~Model() {}

void Model::forward(cv::Mat image, std::vector<Rect>* faces, std::vector<int>* ids;) {
    std::vector<std::vector<float>> numerical_reps;

    localizer.localize_update(image, faces); // hopefully this loads up faces with faces :)
    for (int i = 0; i < faces.size(); i ++) {detector.vector_transform_update(image, faces[i], numerical_reps);}
    for (int i = 0; i < faces.size(); i ++) {ids.push_back(classifier.classify(numerical_reps[i], data));}
}

vector<float> Model::forward(cv::Mat image) {
    std::vector<Rect> faces;
    std::vector<int> ids;
    forward(image, faces, ids);
    return ids;
}