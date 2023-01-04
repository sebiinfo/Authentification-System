//
// Created by sebastian_simon on 01/12/2022.
//

#ifndef AUTHENTICATION_SYSTEM_CLASSIFICATION_HPP
#define AUTHENTICATION_SYSTEM_CLASSIFICATION_HPP

#include "../Interfaces/Facedata.hpp"
#include "../Interfaces/best_split_type.hpp"
#include <iostream>
#include <opencv2/core/mat.hpp>

/*

// should we use a namespace?
class Classifier {
  public:
    std::vector<Facedata> data;
    int dimension_data, length_vector;

    Classifier(std::vector<Facedata> data);
    
    // ~Classification();
};

*/

class Classifier {
  public:
    Classifier(int num_people, int dim);
    Classifier(int num_people, int dim, std::vector<cv::Mat> &num_reps, std::vector<int> &labels);
    ~Classifier();

    virtual void train(std::vector<cv::Mat> &num_reps; std::vector<int> &labels);
    virtual int classify(cv::Mat &image);

  private:
    int num_people;
    int dim;
    std::vector<cv:Mat> num_reps; // numerical representations of the faces
    std::vector<int> labels;
};

class Node {
  public:
    Node *left_child_pointer;
    Node *right_child_pointer;
    std::vector<Facedata> node_data;
    static std::string info_measure;
    // node_data is the data the node has stored, the root having node_data=data

    Node(std::vector<Facedata> &node_data,
         std::string info_measure = "entropy");

    //~Node();

    static double get_information_gain(std::vector<int> id_vector);
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
    DecisionTree(std::vector<Facedata> data);

    //~DecisionTree();

    void build_tree(Node *node_pointer);

    int classify(Facedata query);
    // int max_depth;    it is a choice weather we do it
};

#endif // AUTHENTICATION_SYSTEM_CLASSIFICATION_HPP
