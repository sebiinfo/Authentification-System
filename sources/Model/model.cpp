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
    this->localizer = localizer(width, height);
    this->vectorizer = vectorizer(num_people, num_feature);
    this->classifier = classifier(num_people, num_feature);
}

Model::~Model() {}

void Model::predict(cv::Mat image, std::vector<cv::Rect>* faces, std::vector<int>* ids) {
    std::vector<cv::Mat> numerical_reps;

    /* localizer.localize_update(
        image, faces); // hopefully this loads up faces with faces :)
    vectorizer.vectorize_update(image, faces[i], numerical_reps);
    for (int i = 0; i < faces.size(); i++) {
        ids.push_back(classifier.classify(numerical_reps[i]));
    } */
}

std::vector<int> Model::predict(cv::Mat &image) {
    std::vector<cv::Rect> faces;
    std::vector<int> ids;
    predict(image, faces, ids);
    return ids;
}

void Model::load_train_images() {
    std::cout << "Loading Training Images" << std::endl;
    std::string filename, base_filename;
    for (int label = 1; label <= num_people; label++) {
        base_filename = "./yalefaces/train/" + std::to_string(label) + "/";
        for (int i = 1; i <= 9; i++) {
            filename = base_filename + std::to_string(i);
            filename = filename + ".png";
            cv::Mat image = cv::imread(filename);
            cv::Mat flat_image = image.reshape(1, 1);
            train_images.push_back(flat_image);
            train_labels.push_back(label);
        }
    }
    std::cout << "Finished Loading" << std::endl;
}
