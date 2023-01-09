#ifndef AUTHENTICATION_SYSTEM_KNN
#define AUTHENTICATION_SYSTEM_KNN

#include "classifier.hpp"
#include <opencv2/core/mat.hpp>
#include <vector>

class KNN : public Classifier {
public:
    int k;

    KNN(int num_people, int dim, std::vector<cv::Mat> &num_reps,
        std::vector<int> &labels);

    bool compare(const cv::Mat &v1, const cv::Mat &v2) const;

    int classify(const cv::Mat &query);

    // computes Euclidian distance between a
    double compute_distance(cv::Mat vect) const;

    int dim;
    int num_people;
    static cv::Mat query;
    std::vector<cv::Mat> num_reps;
    std::vector<int> labels;
    ~KNN();
    // query and ith vector in data
};

#endif
