//
// Created by sebas on 08/01/2023.
//
#include "decisiontree.hpp"

#include <iostream>
#include <utility>
Node::Node(int num_people, int dim, std::vector<cv::Mat> &num_reps,
           std::vector<int> &labels, const std::string &info_measure) {
   this->left_child_pointer = nullptr;
   this->right_child_pointer = nullptr;
   this->dim = dim;
   this->num_reps = num_reps;
   this->num_people = num_people;
   this->labels = labels;
   this->info_measure = info_measure;
   this->best_split = get_best_split();
}

Node::~Node() {
   num_reps.clear();
   labels.clear();
   info_measure.clear();

   while (left_child_pointer != nullptr) {
      Node *current_pointer = left_child_pointer->left_child_pointer;
      delete left_child_pointer;
      left_child_pointer = current_pointer;
   }

   while (right_child_pointer != nullptr) {
      Node *current_pointer = right_child_pointer->right_child_pointer;
      delete right_child_pointer;
      right_child_pointer = current_pointer;
   }
}

double Node::get_information_gain(std::vector<int> id_vector) const {
   std::map<int, int> id_freq;
   unsigned long long length_vector = id_vector.size();
   for (int i = 0; i < length_vector; ++i) {
      if (id_freq.count(id_vector[i])) {
         id_freq[id_vector[i]] += 1;
      } else {
         id_freq[id_vector[i]] = 1;
      }
   }
   std::vector<double> freq_vector;
   //std::cout << "Printing id_freq" << "\n";
   //for(auto key: id_freq){
      //std::cout << key.first << " " << key.second <<" ";
      //std::cout << "\n";
   //}

   // above we will keep the vector of probabilities of each element
   for (auto &it : id_freq) {
      freq_vector.push_back(double(it.second) / double(length_vector));
   }
   //std::cout << "Freq Vector" << "\n";
   //for (auto i : freq_vector) {
      //std::cout << i << " ";
   //}


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

double Node::split_and_give_information(int entry, double threshold) {
   std::vector<int> labels_group1, labels_group2;
   for (int i = 0; i < num_people; ++i) {
      if (num_reps[i].at<double>(0, entry) <= threshold) {
         labels_group1.push_back(labels[i]);
      } else {
         labels_group2.push_back(labels[i]);
      }
   }

   // if (info_measure=="entropy"){
   double entropy_group1 = Node::get_information_gain(labels_group1);
   double entropy_group2 = Node::get_information_gain(labels_group2);

   return entropy_group1 * double(double(labels_group1.size() )/ num_people) +
          entropy_group2 * double(double(labels_group2.size() )/ num_people);
   //}
   // I believe that for both gini impurity and entropy the combined information
   // is a linear sum
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
   std::vector<std::vector<double>> all_thresholds;
   // all_thresholds[i] contains all the thresholds in our data on position i
   // we start by initializing this vector
   for (int i = 0; i < dim; ++i) {
      all_thresholds.push_back(get_thresholds(i));
   }
   // now we need to look over all the possible splits and choose
   // the one which gives the best information

   best_split_type final_split{};
   final_split.information_gain = INFINITY;

   for (int i = 0; i < dim; ++i) {
      for (auto j : all_thresholds[i]) {
         // threshold j at position i
         // now we need to separate all the vectors in our dataset based on this
         // query
         double current_information = Node::split_and_give_information(i, j);
         
         if (current_information < final_split.information_gain) {
            final_split.information_gain = current_information;
            final_split.threshold = j;
            final_split.entry = i;
         }
      }
   }
   return final_split;
}

int Node::is_pure() {
   if (labels.empty()) {
      return -1;
   }
   const double limit = 0.9;
   std::map<int, int> id_freq;
   for (int label : labels) {
      if (id_freq.count(label)) {
         id_freq[label] += 1;
      } else {
         id_freq[label] = 1;
      }
   }
   for (auto &it : id_freq) {
      if (it.second > limit * num_people) {
         return it.first;
      }
   }
   return -1;
}

DecisionTree::DecisionTree(int num_people, int dim): Classifier(num_people, dim) {

}

DecisionTree::DecisionTree(int num_people, int dim,
                           std::vector<cv::Mat> &num_reps,
                           std::vector<int> &labels)
    : Classifier(num_people, dim, num_reps, labels) {
   root = new Node(num_people, dim, num_reps, labels);
   build_tree(root);
}

DecisionTree::~DecisionTree() {
   for (auto representation : num_reps) {
      representation.release();
   }
   num_reps.clear();
   labels.clear();
}

void DecisionTree::build_tree(Node *current_node_pointer) {
   // we need to initialize a Node object containing all the data
   // when we de the initialization we already have the best split
   //  Node current_node=Node(num_people, dim, num_reps, labels);

   // we initialize the node label: -1 if not pure, the label otherwise
   current_node_pointer->node_label = current_node_pointer->is_pure();
   // we only build a children of the Node if not pure
   if (current_node_pointer->node_label != -1) {
      return;
   }

   // we get the coordinate and threshold for the best split
   // now we need to split accordingly to make the left and right nodes
   std::vector<int> labels_left, labels_right;
   std::vector<cv::Mat> num_reps_left, num_reps_right;

   int split_entry = current_node_pointer->best_split.entry;
   double split_threshold = current_node_pointer->best_split.threshold;

   for (int i = 0; i < current_node_pointer->num_people; ++i) {
      if (current_node_pointer->num_reps[i].at<double>(0, split_entry) <=
          split_threshold) {
         num_reps_left.push_back(current_node_pointer->num_reps[i]);
         labels_left.push_back(current_node_pointer->labels[i]);
      } else {
         num_reps_right.push_back(current_node_pointer->num_reps[i]);
         labels_right.push_back(current_node_pointer->labels[i]);
      }
   }

   // we create pointers to the two new nodes
   Node *node_left =
       new Node(int(num_reps_left.size()), dim, num_reps_left, labels_left);
   Node *node_right =
       new Node(int(num_reps_right.size()), dim, num_reps_right, labels_right);

   current_node_pointer->left_child_pointer = node_left;
   current_node_pointer->right_child_pointer = node_right;

   // now we need to construct
   DecisionTree::build_tree(current_node_pointer->left_child_pointer);
   DecisionTree::build_tree(current_node_pointer->right_child_pointer);
}
int DecisionTree::classify(cv::Mat query) {
   // we initialize the node with the faces
   if (is_alienated(query)){
       return -1;
   }

   Node *parent_node = new Node(num_people, dim, num_reps, labels);

   // while the node is not pure we go to the corresponding child
   while (parent_node->node_label == -1) {
      int split_entry = parent_node->best_split.entry;
      double split_threshold = parent_node->best_split.threshold;
      if (query.at<double>(0, split_entry) <= split_threshold) {
         parent_node = parent_node->left_child_pointer;
      } else {
         parent_node = parent_node->right_child_pointer;
      }
   }
   // when we exit the while we have a pure node
   return parent_node->node_label;
}
