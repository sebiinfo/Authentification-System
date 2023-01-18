#include "model.hpp"
#include "../Localization/localizer.hpp"
#include "../Localization/cascadecv.hpp"
#include "../Vectorization/vectorizer.hpp"
#include "../Vectorization/fisher.hpp"
#include "../Classification/classifier.hpp"
#include "../Classification/knn.hpp"
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

//    if (localizer == "Cascade") {this->localizer = new Cascade_Detector_CV(width, height);}
  //  else {assert(false);}

    if (vectorizer == "Fisher") {this->vectorizer = new Fisher(num_people, num_feature);}
    else {assert(false);}

    if (classifier == "KNN") {this->classifier = new KNN(num_people, num_feature);}
    else {assert(false);}
    //KNN constructor has 4 arguments. For the moment leave this commented.

    this->load_train_images();
    this->vectorizer->train(train_images, train_labels);
    this->classifier->train(train_images, train_labels);
}

Model::~Model() {
    //delete localizer;
    delete vectorizer;
    delete classifier;
}

std::vector<int> Model::predict(cv::Mat & image, std::vector<cv::Rect> & faces) {
    std::vector<cv::Mat> in_faces = localizer->localize(image, faces);
    std::vector<int> output;
    for (int i = 0; i < in_faces.size(); i++) {
        cv::Mat numerical_reps = vectorizer->vectorize(in_faces[i]);
        output.push_back(classifier->classify(numerical_reps));
    }
    return output;


    /* localizer.localize_update(
        image, faces); // hopefully this loads up faces with faces :)
    vectorizer.vectorize_update(image, faces[i], numerical_reps);
    for (int i = 0; i < faces.size(); i++) {
        ids.push_back(classifier.classify(numerical_reps[i]));
    } */
}

std::vector<int> Model::predict(cv::Mat & image) {
    std::vector<cv::Rect> faces;
    return predict(image, faces);
}

int Model::predict_most_likely(cv::Mat & image) {
    std::vector<int> temp = predict(image);
    if (temp.size() == 0) {return -1;}
    else {return temp[0];}
    // in future we need to use the rect and consider which face is the main one.
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
