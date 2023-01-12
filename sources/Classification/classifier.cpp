#include "classifier.hpp"

//#include <bits/stdc++.h>
#include <math.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <set>

Classifier::Classifier(int num_people, int dim) {
   // if (data[0].entries.rows > 1) {
   //   throw "data has wrong dimensions";
   //}
   this->num_people = num_people;
   this->dim = dim;
}

Classifier::Classifier(int num_people, int dim, std::vector<cv::Mat> &num_reps,
                       std::vector<int> &labels) {
   this->num_people = num_people;
   this->dim = dim;

   if (num_reps.size() != labels.size()) {
      throw "vectors of characteristics and ids have different lengths";
   }

   this->num_reps = num_reps;
   this->labels = labels;
}


void Classifier::train(std::vector<cv::Mat> &num_reps,
                       std::vector<int> &labels) {
   this->num_reps = num_reps;
   this->labels = labels;
}

Classifier::~Classifier() = default;
