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
    int knn (cv::Mat query, int dimension, vector_id data ){
        //should return the id of the k nearest neighbours
    };
};