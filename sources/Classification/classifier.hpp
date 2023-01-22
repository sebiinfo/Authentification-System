//
// Created by sebastian_simon on 01/12/2022.
//

#ifndef AUTHENTICATION_SYSTEM_CLASSIFICATION_HPP
#define AUTHENTICATION_SYSTEM_CLASSIFICATION_HPP

#include <iostream>
#include <opencv2/core/mat.hpp>

#include "../Interfaces/Facedata.hpp"
#include "../Interfaces/best_split_type.hpp"

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
    /*The class classifier is the parent class which will inherit all the
     * classification algorithms It has as attributes the number of people in
     * the dataset, num_people, the vectors representing the faces in num_reps
     * and their dimension dim, and labels which contains the id of each face
     * This class will be called by the model class and loaded with the proper
     * data
     */

  public:
    Classifier() = default;
    Classifier(int num_people, int dim);
    Classifier(int num_people, int dim, std::vector<cv::Mat> &num_reps,
               std::vector<int> &labels);
    ~Classifier();

    // loads num_reps and labels in case the first classifier is used
    virtual void train(std::vector<cv::Mat> &num_reps,
                       std::vector<int> &labels);

    // the function which is overwritten by the inherited algorithm class
    // it return the id of the person that it matches with the most
    // or -1 if it is too far away from all the people
    virtual int classify(const cv::Mat &image);
    double compute_distance(const cv::Mat &mat1, const cv::Mat &mat2) const;
    // this is a function which checks weather the query is too far off from all
    // the groups
    //  returns true iff the person if too far off
    bool is_alienated(const cv::Mat &query);

    // helper function for is_alienated which checks alienation on people with
    // label : id
    bool is_alienated_id_normal(const cv::Mat &query, int id);
    bool is_alienated_id_linear(const cv::Mat &query, int id);

    // the alienation constant is the percentage of admissible alienated
    // coordinates
    double alienation_constant = 0.1; //above 1 not doing the feature
    int num_people{};
    int dim{};
    std::vector<cv::Mat> num_reps; // numerical representations of the faces
    std::vector<int> labels;
};

#endif // AUTHENTICATION_SYSTEM_CLASSIFICATION_HPP
