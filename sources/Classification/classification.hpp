//
// Created by sebastian_simon on 01/12/2022.
//

#ifndef AUTHENTICATION_SYSTEM_CLASSIFICATION_HPP
#define AUTHENTICATION_SYSTEM_CLASSIFICATION_HPP

#endif // AUTHENTICATION_SYSTEM_CLASSIFICATION_HPP

#include "../Interfaces/Facedata.hpp"
#include <iostream>
#include <opencv2/core/mat.hpp>

class Classification {
  public:
    std::vector<Facedata> data;
    int dimension_data, length_vector;

    Classification(std::vector<Facedata> data);
    ~Classification();
};

class KNN : public Classification {
  public:
    int k;
    KNN(std::vector<Facedata> data);
    double compute_distance(Facedata query,
                            int i); // computes Euclidian distance between a
                                    // query and ith vector in data
    static bool compare(Facedata v1, Facedata v2);
    int classify(Facedata query);
};
