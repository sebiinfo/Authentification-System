//
// Created by sebastian_simon on 01/12/2022.
//

#ifndef AUTHENTICATION_SYSTEM_CLASSIFICATION_HPP
#define AUTHENTICATION_SYSTEM_CLASSIFICATION_HPP

#endif //AUTHENTICATION_SYSTEM_CLASSIFICATION_HPP

#include <iostream>
#include <opencv2/core/mat.hpp>
#include "vector_id.hpp"

class Classification{
public:
    std::vector<vector_id> data;
    int dimension_data, length_vector;

    Classification(std::vector<vector_id> data);
    ~Classification();


};

class KNN : public Classification{
public:
    int k;
    KNN(std::vector<vector_id> data);
    double compute_distance (vector_id query, int i); // computes Euclidian distance between a query and ith vector in data
    static bool compare (vector_id v1, vector_id v2);
    int classify(vector_id query);
};