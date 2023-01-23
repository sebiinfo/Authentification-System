#include "model.hpp"
#include "../Classification/classifier.hpp"
#include "../Classification/decisiontree.hpp"
#include "../Classification/knn.hpp"
#include "../Localization/localizer.hpp"
#include "../Localization/localizer_cascade.hpp"
#include "../Vectorization/fisher.hpp"
#include "../Vectorization/vectorizer.hpp"
#include <cassert>
#include <config.h>
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/highgui.hpp>
#include <string>

static void debug_print(cv::Mat temp) {
    std::cout << "temp.dims = " << temp.dims << " temp.size = [";
    for (int i = 0; i < temp.dims; ++i) {
        if (i)
            std::cout << " X ";
        std::cout << temp.size[i];
    }
    std::cout << "] temp.channels = " << temp.channels() << std::endl;
}

static int calculate_score(cv::Mat &image, cv::Rect &face) {
    int x = abs(face.x + face.x + face.height - image.rows);
    int y = abs(face.y + face.y + face.width - image.cols);
    return face.width * face.height * 4 - pow(x, 2) - pow(y, 2);
}

Model::Model(int num_people, int num_feature, int width, int height,
             std::string localizer, std::string vectorizer,
             std::string classifier) {
    this->num_people = num_people;
    this->num_feature = num_feature;
    this->width = width;
    this->height = height;
    this->load_train_images();
    debug_print(train_images[0]);

    std::cout << "Training the Vectorizer" << std::endl;
    if (vectorizer == "Fisher") {
        this->vectorizer =
            new Fisher(num_people, num_feature, train_images, train_labels);
    } else {
        assert(false);
    }

    std::cout << "Training the Classifier"
              << " " << classifier << std::endl;
    std::cout << num_people << " " << num_feature;
    for (auto v : train_images) {
        std::cout << v << std::endl;
    }

    if (classifier == "KNN") {
        this->classifier =
            new KNN(num_people, num_feature, train_images, train_labels);
    } else if (classifier == "DecisionTree") {
        this->classifier = new DecisionTree(num_people, num_feature,
                                            train_images, train_labels);
    } else {
        assert(false);
    }
    std::string path = "/resources/temp.jpg";
    path = std::string(PATH_TO_RESOURCES) + path;
    cv::Mat image =
        cv::imread(path);
    image = image.reshape(1, 1);
    // debug_print(image);
    std::cout << "trying to predict\n\n"<<std::endl;
    cv::Mat num_rep = this->vectorizer->vectorize(image);
    std::cout << num_rep << std::endl;
    predicted_label =
        this->classifier->classify(this->vectorizer->vectorize(image));
    std::cout << "This is the output of first img " << predicted_label
              << std::endl;

    // KNN constructor has 4
    // arguments. For the moment leave this commented.
    //    std::cout<<"trained labels are \n";
    //    for (auto i: this->classifier->labels){
    //        std::cout<<i<<" ";
    //    }

    //    this->classifier->train(train_images, train_labels);
}

Model::~Model() {
    delete vectorizer;
    delete classifier;
}

std::vector<int> Model::predict(cv::Mat &image) {
    cv::Mat new_image = image.clone();
    // image.copyTo(new_image);
    // std::vector<cv::Mat> in_faces = localizer->Transform(image);
    std::vector<int> output;
    std::cout << "\n\n\nVectorizing\n" << std::endl;
    std::cout << "Italia suge pula" << std::endl;
    // cv::Mat numerical_reps = vectorizer->vectorize(image);
    std::cout << "Maldive suge pula" << std::endl;

    // std::cout << "Numerical rep is\n" << numerical_reps << std::endl;
    // debug_print(numerical_reps);
    std::cout << "Classifying\n";
    output.push_back(
        this->classifier->classify(this->vectorizer->vectorize(new_image)));
    std::cout << "Finished\n" << std::endl;
    return output;
}

// int Model::predict_most_likely(cv::Mat &image)
//{
//     std::vector<cv::Rect> faces;
//     std::vector<int> temp = predict(image, faces);
//     if (temp.size() == 0)
//     {
//         return -1;
//     }
//     else
//     {
//         int score = -1e9;
//         int output = -1;
//         for (int i = 0; i < temp.size(); i++)
//         {
//             if (calculate_score(image, faces[i]) > score)
//             {
//                 output = i;
//                 score = calculate_score(image, faces[i]);
//             }
//         }
//         return temp[output];
//     }
//     // in future we need to use the rect and consider which face is the main
//     // one.
// }

void Model::load_train_images() {
    std::cout << "Loading Training Images" << std::endl;
    std::string filename, base_filename;
    for (int label = 1; label <= num_people; label++) {
        base_filename = "./resources/" + std::to_string(label) + "/";
        for (int i = 0; i <= 9; i++) {
            filename = base_filename + std::to_string(i);
            filename = filename + ".jpg";
            // std::cout << filename << std::endl;
            cv::Mat image = cv::imread(filename);
            cv::Mat flat_image = image.reshape(1, 1);
            train_images.push_back(flat_image);
            train_labels.push_back(label);
        }
    }
    std::cout << "Finished Loading" << std::endl;
}
