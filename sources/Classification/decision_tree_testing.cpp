
#include "decision_tree_testing.hpp"

#include <iostream>
#include <opencv2/core/mat.hpp>
#include <vector>

std::vector<double> Testing_Functions::generate_random_vector(int dim) {
   // Generates a random line vector with varialble size
   std::random_device rd;
   auto seed = std::chrono::system_clock::now().time_since_epoch().count();
   std::mt19937 gen(seed);
   std::uniform_real_distribution<> dis(0, 10.0);

   std::vector<double> result(dim);

   for (int i = 0; i < result.size(); i++) {
      result[i] = dis(gen);
   }
   return result;
}

std::vector<int> Testing_Functions::generate_random_id(int num_people) {
   // generates a random list of ids corresponding to a vector of faces
   std::vector<int> result(num_people);

   for (auto &face : result) {
      face = rand() % 10000;
      face = face % 4;
   }

   return result;
}

std::vector<cv::Mat> Testing_Functions::generate_faces(int num_people,
                                                       int dim) {
   // generates faces from line_vectors
   std::vector<cv::Mat> faces_vector(num_people);

   for (auto &face : faces_vector) {
      face = cv::Mat(generate_random_vector(dim), true);
   }

   return faces_vector;
}

void Testing_Functions::print_best_split(best_split_type best_split) {
   std::cout << "Entry: " << best_split.entry
             << "\n Information Gain: " << best_split.information_gain
             << "\n Threshold :" << best_split.threshold;
}

void Testing_Node::split_and_give_information(Node *node, int entry,
                                              double threshold) {
   std::cout << "Split and Give Iformation: "
             << node->split_and_give_information(entry, threshold);
}

void Testing_Node::test_get_best_split(Node *node) {
   best_split_type best_split = node->get_best_split();
   Testing_Functions::print_best_split(best_split);
}

void Testing_Node::get_thresholds(Node *node, int entry) {
   Testing_Functions::print_vector(node->get_thresholds(entry));
}

void Testing_Node::print_node(Node *node) {
   Testing_Functions::print_vector(node->labels);
   Testing_Functions::print_vector_mat(node->num_reps);
   Testing_Functions::print_best_split(node->best_split);

   std::cout << "Info measure: " << node->info_measure << "\n";
   std::cout << "Node instance: " << node->node_label << "\n";
}
Node *Testing_Node::create_node(int num_people, int dim) {
   auto num_reps = Testing_Functions::generate_faces(num_people, dim);
   auto labels = Testing_Functions::generate_random_id(num_people);
   return new Node(num_people, dim, num_reps, labels);
}
DecisionTree *Testing_Decision_Tree ::build_tree(int num_people, int dim) {
   auto num_reps = Testing_Functions::generate_faces(num_people, dim);
   auto labels = Testing_Functions::generate_random_id(num_people);
   DecisionTree *decision_tree =
       new DecisionTree(num_people, dim, num_reps, labels);
   return decision_tree;
}
void Testing_Decision_Tree::Testing_Build_Tree(int num_people, int dim) {
   DecisionTree *decision_tree =
       Testing_Decision_Tree::build_tree(num_people, dim);
}

