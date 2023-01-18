#ifndef AUTHENTICATION_SYSTEM_VECTOR_ID_HPP
#define AUTHENTICATION_SYSTEM_VECTOR_ID_HPP

#include <opencv2/core/mat.hpp>

struct [[maybe_unused]] Facedata {
    int id;
    cv::Mat_<double> entries;
    double distance_to_query; // for knn this will be the distance to the querry
};
#endif // AUTHENTICATION_SYSTEM_VECTOR_ID_HPP