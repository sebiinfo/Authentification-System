#include "classification.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <math.h>
#include <bits/stdc++.h>
#include <set>


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
    //todo check weather we need a weigthed sum
    double sum = 0;
    for (int cont = 0; cont < length_vector; ++cont) {
        sum += pow((query.entries.at<double>(0, cont) -
                    data[i].entries.at<double>(0, cont)),
                   2);
    }
    return sqrt(sum);
}

bool KNN::compare(const Facedata& v1, const Facedata& v2) {
    return (v1.distance_to_query < v2.distance_to_query);
}

int KNN::classify(const Facedata& query) {
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
            id_freq[data[i].id] = 1;
        }
    }
    int max_freq = 0, max_id;
    for (auto & it : id_freq) {
        if (it.second > max_freq) {
            max_id = it.first;
            max_freq = it.second;
        }
    }
    return max_id;
}


double Node::get_information_gain(std::vector<int> id_vector){
    std::map<int, int> id_freq;
    unsigned long long length_vector = id_freq.size();
    for (int i = 0; i < length_vector; ++i) {
        if (id_freq.count(id_vector[i])) {
            id_freq[id_vector[i]] += 1;
        } else {
            id_freq[id_vector[i]] = 1;
        }
    }
    std::vector<double> freq_vector;
    //above we will keep the vector of probabilities of each element
    for (auto &it: id_freq) {
        freq_vector.push_back(double(it.second) / double(length_vector));
    }

    if (info_measure == "entropy") {
        double entropy = 0;
        for (auto i: freq_vector) {
            entropy += -double(i) * double(log2(i));
        }
        return entropy;
    }
    if (info_measure == "gini") {
        double gini_index = 0;
        for (auto i: freq_vector) {
            gini_index += double(i) * double(i);
        }
        return 1 - gini_index;
    }
    return 0;
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

best_split_type Node::get_best_split() {
    std::vector<std::vector<double>> all_thresholds;
    // all_thresholds[i] contains all the thresholds in our data on position i
    // we start by initializing this vector
    for(int i=0; i<node_data.size(); ++i){
        all_thresholds.push_back(get_thresholds(i));
    }
    //now we need to look over all the possible splits and choose
    //the one which gives the best information
    for (int i=0; i<all_thresholds.size(); ++i){
        for (auto j: all_thresholds[i]){
            //threshold j at position i

        }
    }

}

