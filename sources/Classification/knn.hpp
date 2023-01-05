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

    static bool compare(const cv::Mat &v1, const cv::Mat &v2);

    int classify(const cv::Mat &query);

    // computes Euclidian distance between a
    double compute_distance(cv::Mat query, int i); 
    std::vector<double>distance_to_query;
    int dim;
    int num_people;
    std::vector<cv::Mat> num_reps;
    std::vector<cv::Mat> labels;
     
    // query and ith vector in data
};

#endif
