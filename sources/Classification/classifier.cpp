#include "classifier.hpp"
#include <algorithm>
#include <bits/stdc++.h>
#include <iostream>
#include <map>
#include <math.h>
#include <set>

Classifier::Classifier(std::vector<Facedata> data) {
    if (data[0].entries.rows > 1) {
        throw "data has wrong dimensions";
    }
    this->data = data;
    this->dimension_data = data.size();
    this->length_vector = data[0].entries.cols;
}

double Node::get_information_gain(std::vector<int> id_vector) {
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
    // above we will keep the vector of probabilities of each element
    for (auto &it : id_freq) {
        freq_vector.push_back(double(it.second) / double(length_vector));
    }

    if (info_measure == "entropy") {
        double entropy = 0;
        for (auto i : freq_vector) {
            entropy += -double(i) * double(log2(i));
        }
        return entropy;
    }
    if (info_measure == "gini") {
        double gini_index = 0;
        for (auto i : freq_vector) {
            gini_index += double(i) * double(i);
        }
        return 1 - gini_index;
    }
    return 0;
}

std::vector<double> Node::get_thresholds(int entry) {
    std::set<double> threshold_set;
    for (auto &face : node_data) {
        threshold_set.insert(face.entries.at<double>(0, entry));
    }
    std::vector<double> thresholds;

    for (auto &t : threshold_set) {
        thresholds.push_back(t);
    }
    return thresholds;
}

best_split_type Node::get_best_split() {
    std::vector<std::vector<double>> all_thresholds;
    // all_thresholds[i] contains all the thresholds in our data on position i
    // we start by initializing this vector
    for (int i = 0; i < node_data.size(); ++i) {
        all_thresholds.push_back(get_thresholds(i));
    }
    // now we need to look over all the possible splits and choose
    // the one which gives the best information
    for (int i = 0; i < all_thresholds.size(); ++i) {
        for (auto j : all_thresholds[i]) {
            // threshold j at position i
        }
    }
}
