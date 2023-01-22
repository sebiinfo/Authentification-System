#ifndef AUTHENTICATION_SYSTEM_MODEL_HPP
#define AUTHENTICATION_SYSTEM_MODEL_HPP

#include "../Classification/classifier.hpp"
#include "../Localization/localizer.hpp"
#include "../Vectorization/vectorizer.hpp"
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <string>

class Model {
    /*
    A class that connects the components of algorithm together to create a
    complete facial classifier Components (for now):
      - A localization components that takes in a an image and localizes it to
    the faces, then reshapes them
      - A detechor components that transforms the image to vectors of number,
    numerical-representing it
      - A classifier that classifies the vectors of number into an ID, or
    the -1 ID (for any weirdo) with respect to a data

    The data are train_images and train_label. Tbey would be
    referred to by the "model" upon running. The
    num_feature's default value would be decided later by the team. The
    placeholders for the components are of type ints for now. Base types are on
    the way. Data types to work with (for now): cv::Vec, cv::Mat, cv::Rect,
    Facedata::Facedata
    */

  public:
    Model(int num_people, int num_feature, int width, int height,
          std::string localizer, std::string vectorizer,
          std::string classifier);
    ~Model();
    // std::vector<int> predict(cv::Mat &image, std::vector<cv::Rect> &faces);
    std::vector<int> predict(cv::Mat &image);
    //    int predict_most_likely(cv::Mat &image);
    Classifier *classifier;
    Vectorizer *vectorizer;
    Localizer *localizer;

  private:
    void load_train_images();

    int num_people;
    int num_feature;
    int width;
    int height;
    std::vector<cv::Mat> train_images;
    std::vector<int> train_labels;
};

#endif // AUTHENTICATION_SYSTEM_MODEL_HPP
