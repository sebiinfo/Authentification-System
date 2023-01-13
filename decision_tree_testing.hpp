#include <iostream>
#include <opencv2/core/mat.hpp>
#include <random>
#include <vector>

#include "decisiontree.hpp"

class RandomFunctions {
 public:
   RandomFunctions() {}
   static std::vector<double> generate_random_vector(int dim);
   static std::vector<int> generate_random_id(int num_people);
   static std::vector<cv::Mat> generate_faces(int num_people, int dim);
    

   template <typename T>
   static void print_vector(std::vector<T> my_vector) {
      for (const auto &element : my_vector) {
         std::cout << element << " ";
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
   Testing_Node(int num_people, int dim);
   std::vector<int> labels;
   std::vector<cv::Mat> num_reps;
   int dim;
   int num_people;
   void test_get_best_split();
   void test_is_pure();
   void split_and_give_information(int entry, double threshold);
   void get_information_gain(std::vector<int> id_vector);

};
