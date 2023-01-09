//
// Created by sebas on 08/01/2023.
//

#ifndef AUTHENTICATION_SYSTEM_DECISIONTREE_HPP
#define AUTHENTICATION_SYSTEM_DECISIONTREE_HPP

#endif //AUTHENTICATION_SYSTEM_DECISIONTREE_HPP

#include "classifier.hpp"

#include <bits/stdc++.h>
#include <math.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <set>

class Node {
public:
    Node *left_child_pointer{};
    Node *right_child_pointer{};
   // std::vector<Facedata> node_data;               instead of FaceData we now use a different data format
    int dim;
    int num_people;
    std::vector<cv::Mat> num_reps;
    std::vector<int> labels;
    std::string info_measure;
    best_split_type best_split;
    // node_data is the data the node has stored, the root having node_data=data

    Node(int num_people, int dim, std::vector<cv::Mat> &num_reps,
         std::vector<int> &labels,  const std::string &info_measure="entropy");

    //~Node();

    double get_information_gain(std::vector<int> id_vector);
    // the information gain can be either computed with the gini index or
    // entropy we set info_type to "entropy" and it can be manually adjusted to
    // "gini"

    std::vector<double> get_thresholds(int entry);
    // this function retracts the values of all the thresholds in entry from
    // node_data

    best_split_type get_best_split();
    // we instantly look for the best split everytime we build a node
};

class DecisionTree : public Classifier {
public:
    DecisionTree(int num_people, int dim, std::vector<cv::Mat> &num_reps,
                 std::vector<int> &labels);

    //~DecisionTree();

    void build_tree(Node *node_pointer);

    int classify(Facedata query);
    // int max_depth;    it is a choice weather we do it
};
