//
// Created by sebas on 08/01/2023.
//

#ifndef AUTHENTICATION_SYSTEM_DECISIONTREE_HPP
#define AUTHENTICATION_SYSTEM_DECISIONTREE_HPP

#endif  // AUTHENTICATION_SYSTEM_DECISIONTREE_HPP

#include <bits/stdc++.h>
#include <math.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <set>

#include "classifier.hpp"

class Node {
 public:
   /*The nodes are nodes of the decision tree, and they store the information
    * We use a cv::Mat object and a list of labels to keep the data !!!ONLY
    * MODIFY THEM TOGETHER!!! We no longer use the Facedata struct for
    * optimization reasons
    */

   // Pointer to the left and right child
   Node *left_child_pointer;
   Node *right_child_pointer;

   int dim;
   int num_people;
   std::vector<cv::Mat> num_reps;
   std::vector<int> labels;
   std::string info_measure;
   best_split_type best_split{};
   int node_label = -1;

   Node(){}

   Node(int num_people, int dim, std::vector<cv::Mat> &num_reps,
        std::vector<int> &labels, const std::string &info_measure = "entropy");

   ~Node();

   double get_information_gain(std::vector<int> id_vector);
   // the information gain can be either computed with the gini index or
   // entropy we set info_type to "entropy" and it can be manually adjusted to
   // "gini"

   double split_and_give_information(int entry, double threshold);
   // this function takes a face splits it in entry with value threshold and
   // gives either the gini index or information leakage

   std::vector<double> get_thresholds(int entry);
   // this function retracts the values of all the thresholds in entry from
   // node_data

   best_split_type get_best_split();
   // we instantly look for the best split everytime we build a node

   int is_pure();
   // return the label if the node is pure and -1 otherwise
};

class DecisionTree : public Classifier {
 public:
    /*The decision tree class which builds the tree and classifies the query to a certain id using
     * the class node to store the data
     */
   DecisionTree () {}
   DecisionTree(int num_people, int dim, std::vector<cv::Mat> &num_reps,
                std::vector<int> &labels);

   ~DecisionTree();

   //added a root property 
   Node *root;
   void build_tree(Node *node_pointer);

   int classify(cv::Mat query);
   // int max_depth;    it is a choice weather we do it
};
