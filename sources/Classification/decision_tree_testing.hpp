#include <iostream>
#include <opencv2/core/mat.hpp>
#include <random>
#include <vector>

#include "decisiontree.hpp"

class Testing_Functions {
 public:
   Testing_Functions() {}
   static std::vector<double> generate_random_vector(int dim);
   static std::vector<int> generate_random_id(int num_people);
   static std::vector<cv::Mat> generate_faces(int num_people, int dim);
   static void print_best_split(best_split_type best_split);

   template <typename T>
   static void print_vector(std::vector<T> my_vector) {
      for (const auto &element : my_vector) {
         std::cout << element <<" ";
      }
      std::cout << "\n";
   }
   static void print_vector_mat(std::vector<cv::Mat> my_vector) {
      for (auto &face : my_vector) {
         const double *row_pointer = face.ptr<double>(0);
         for (int i = 0; i < my_vector.size(); i++) {
            std::cout << row_pointer[i] << " ";
         }

         std::cout << " ?-? ";
      }
   }
};

class Testing_Node {
 public:
   Testing_Node(){};
   static void test_get_best_split(Node *node);
   static void test_is_pure(Node *node);
   static void get_thresholds(Node *node, int entry);
   static void split_and_give_information(Node *node, int entry,
                                          double threshold);
   static void get_information_gain(Node *node, std::vector<int> id_vector);
   static void print_node(Node *node);
   static Node *create_node(int num_people, int dim);

};
class Testing_Decision_Tree {
 public:
   Testing_Decision_Tree() {}
   static DecisionTree *build_tree(int num_people, int dim);
   static void Testing_Build_Tree(int num_people, int dim);
   static void print_tree(Node *decision_tree, int current_depth);
};
