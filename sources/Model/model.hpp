#ifndef AUTHENTICATION_SYSTEM_MODEL_HPP
#define AUTHENTICATION_SYSTEM_MODEL_HPP

#endif // AUTHENTICATION_SYSTEM_MODEL_HPP

#include <opencv2/core.hpp>
class Model {
    /*
    A class that connects the components of algorithm together to create a complete facial classifier
    Components (for now): - A localization components that takes in a an image and localizes it to the faces, then reshapes them
                          - A detechor components that transforms the image to vectors of number, numerical-representing it
                          - A classifier that classifies the vectors of number into an ID, or the -1 ID (for any weirdo) with respect to a data
    The data points to a FacialData type. It would be loaded in first thing, and would be would be referred to by the "model" upon running.
    The num_feature's default value would be decided later by the team.
    The placeholders for the components are of type ints for now. Base types are on the way.
    Data types to work with (for now): cv::Vec, cv::Mat
    */
public:
    Model(int localizer, int detector, int classifier, int num_feature, FacialData* data);
    Model(int num_feature, FacialData*data);
    ~Model();

    void forward(cv::Mat image, std::vector<Rect>* faces, std::vector<int>* ids;);
    vector<float> forward(cv::Mat image);

    int num_people;
    int localizer;
    int detector;
    int classifier;
    int num_feature;
    FacialData* data;
    
};
