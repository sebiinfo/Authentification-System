//
// Created by sebas on 08/01/2023.
//
#include "decisiontree.hpp"

#include <opencv2/core/mat.hpp>
#include <opencv2/dnn/utils/inference_engine.hpp>
#include <utility>
<<<<<<< HEAD
#include <vector>

#include "classifier.hpp"
Node::Node(int num_people, int dim, std::vector<cv::Mat> &num_reps,
           std::vector<int> &labels, const std::string &info_measure) {
   this->dim = dim;
   this->num_reps = num_reps;
   this->num_people = num_people;
   this->labels = labels;
   this->info_measure = info_measure;
=======

double Node::get_information_gain(std::vector<int> id_vector)  {
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
>>>>>>> fe09daf8e17f9bc807cfc8ea4e8fa60ed38f4bd8
}

double Node::split_and_give_information(int entry, double threshold) {
    std::vector<int> labels_group1, labels_group2;
    for(int i=0; i<num_people; ++i){
        if (num_reps[i].at<double>(0,entry)<=threshold){
            labels_group1.push_back(labels[i]);
        }
        else{
            labels_group2.push_back(labels[i]);
        }
    }

    //if (info_measure=="entropy"){
        double entropy_group1=Node::get_information_gain(labels_group1);
        double entropy_group2=Node::get_information_gain(labels_group2);
        return entropy_group1*double(labels_group1.size()/num_people)+entropy_group2*double(labels_group2.size()/num_people);
    //}
    //I believe that for both gini impurity and entropy the combined information is a linear sum

}

std::vector<double> Node::get_thresholds(int entry) {
    std::set<double> threshold_set;
    for (auto const &face : num_reps) {
        threshold_set.insert(face.at<double>(0, entry));
    }
    std::vector<double> thresholds;

    for (auto &t : threshold_set) {
        thresholds.push_back(t);
    }
    return thresholds;
}

best_split_type Node::get_best_split() {
<<<<<<< HEAD
   std::vector<std::vector<double>> all_thresholds;
   // all_thresholds[i] contains all the thresholds in our data on position i
   // we start by initializing this vector
   for (int i = 0; i < num_people; ++i) {
      all_thresholds.push_back(get_thresholds(i));
   }
   // now we need to look over all the possible splits and choose
   // the one which gives the best information
   for (auto &all_threshold : all_thresholds) {
      for (auto j : all_threshold) {
         // threshold j at position i
      }
   }
}

Node::~Node() {
   num_reps.clear();
   labels.clear();
   info_measure.clear();

   while (left_child_pointer != NULL) {
      Node *current_pointer = left_child_pointer->left_child_pointer;
      delete left_child_pointer;
      left_child_pointer = current_pointer;
   }

   while (right_child_pointer != NULL) {
      Node *current_pointer = right_child_pointer->right_child_pointer;
      delete right_child_pointer;
      right_child_pointer = current_pointer;
   }
}

DecisionTree::DecisionTree(int num_people, int dim,
                           std::vector<cv::Mat> &num_reps,
                           std::vector<int> &labels)
    : Classifier(num_people, dim, num_reps, labels) {

   this->num_people = num_people;
   this->dim = dim;
   this->num_reps = num_reps;
   this->labels = labels;
}


DecisionTree::~DecisionTree(){

   for(auto representation : num_reps) {
       representation.release();
   }
   num_reps.clear();
   labels.clear();

    
=======
    std::vector<std::vector<double>> all_thresholds;
    // all_thresholds[i] contains all the thresholds in our data on position i
    // we start by initializing this vector
    for (int i = 0; i < dim; ++i) {
        all_thresholds.push_back(get_thresholds(i));
    }
    // now we need to look over all the possible splits and choose
    // the one which gives the best information

    best_split_type final_split{};
    final_split.information_gain=INFINITY;

    for (int i=0; i < dim; ++i) {
        for (auto j : all_thresholds[i]) {
            // threshold j at position i
            //now we need to separate all the vectors in our dataset based on this query
            double current_information=Node::split_and_give_information(i,j);
            if (current_information< final_split.information_gain){
                final_split.information_gain=current_information;
                final_split.threshold=j;
                final_split.entry=i;
            }
        }
    }
    return final_split;
}

Node::Node(int num_people, int dim, std::vector<cv::Mat> &num_reps,
           std::vector<int> &labels,  const std::string &info_measure) {
    this->dim= dim;
    this->num_reps= num_reps;
    this->num_people=num_people;
    this->labels=labels;
    this->info_measure=info_measure;
    //here we need to initialize this->best_split
    this->best_split=Node::get_best_split();

>>>>>>> fe09daf8e17f9bc807cfc8ea4e8fa60ed38f4bd8
}

Node::~Node() {
    num_reps.clear();
    labels.clear();
    info_measure.clear();

    while (left_child_pointer != NULL) {
        Node *current_pointer = left_child_pointer->left_child_pointer;
        delete left_child_pointer;
        left_child_pointer = current_pointer;
    }

    while (right_child_pointer != NULL) {
        Node *current_pointer = right_child_pointer->right_child_pointer;
        delete right_child_pointer;
        right_child_pointer = current_pointer;
    }
}

DecisionTree::DecisionTree(int num_people, int dim,
                           std::vector<cv::Mat> &num_reps,
                           std::vector<int> &labels)
        : Classifier(num_people, dim, num_reps, labels) {

    this->num_people = num_people;
    this->dim = dim;
    this->num_reps = num_reps;
    this->labels = labels;
}


DecisionTree::~DecisionTree(){

    for(auto representation : num_reps) {
        representation.release();
    }
    num_reps.clear();
    labels.clear();


}
