#include "classification.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <math.h>

Classification::Classification(std::vector<Facedata> data) {
    if (data[0].entries.rows > 1) {
        throw "data has wrong dimensions";
    }
    this->data = data;
    this->dimension_data = data.size();
    this->length_vector = data[0].entries.cols;
}

KNN::KNN(std::vector<Facedata> data) : Classification(data) {
    k = int(sqrt(dimension_data));
}

double KNN::compute_distance(Facedata query, int i) {
    double sum = 0;
    for (int cont = 0; cont < length_vector; ++cont) {
        sum += pow((query.entries.at<double>(0, cont) -
                    data[i].entries.at<double>(0, cont)),
                   2);
    }
    return sqrt(sum);
}

bool KNN::compare(Facedata v1, Facedata v2) {
    return (v1.distance_to_query < v2.distance_to_query);
}

int KNN::classify(Facedata query) {
    // first we store in the distance_to_query field of the struct the right
    // distance
    for (int i = 0; i < dimension_data; ++i) {
        data[i].distance_to_query = compute_distance(query, i);
    }
    // now we want to sort the data in terms of the distance, O(nlogn),
    // n-dimensional trees will maybe be implemented later (O(n))
    std::sort(data.begin(), data.end(), compare);

    std::map<int, int> id_freq;
    for (int i = 0; i < k; ++i) {
        if (id_freq.count(
                data[i].id)) { // if the id has appeared before in the map
            id_freq[data[i].id] += 1;
        } else {
            id_freq[data[i].id] = 0;
        }
    }
    int max_freq = 0, max_id;
    for (auto it = id_freq.begin(); it != id_freq.end(); ++it) {
        if (it->second > max_freq) {
            max_id = it->first;
            max_freq = it->second;
        }
    }
    return max_id;
}

std::vector <double>  Node::get_thresholds(int entry) {
    std::set<double> threshold_set;
    for (auto & face : node_data){
        threshold_set.insert(face.entries.at<double>(0, entry));
    }
    std::vector <double> thresholds;

    for (auto & t : threshold_set){
        thresholds.push_back(t);
    }
    return thresholds;
}