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
 public:
   Classifier(int num_people, int dim);
   Classifier(int num_people, int dim, std::vector<cv::Mat> &num_reps,
              std::vector<int> &labels);
   //~Classifier();

   virtual void train(std::vector<cv::Mat> &num_reps, std::vector<int> &labels);
   virtual int classify(cv::Mat &image);


   int num_people;
   int dim;
   std::vector<cv::Mat> num_reps;  // numerical representations of the faces
   std::vector<int> labels;
};


#endif  // AUTHENTICATION_SYSTEM_CLASSIFICATION_HPP
