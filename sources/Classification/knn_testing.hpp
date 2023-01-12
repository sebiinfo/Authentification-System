
#include <iostream>
#include <opencv2/core/mat.hpp>
#include <vector>

#include "knn.hpp"
class KNN_Testing {
 public:
   KNN_Testing(int num_people, int dim);
   std::vector<double> generate_random_vector(int dim);
   std::vector<int> generate_random_id(int num_people);
   std::vector<cv::Mat> generate_faces(int num_people, int dim);
   void test_clasify(int number_faces, int size);

   template <typename T>
   void print_vector(std::vector<T> my_vector) {
      for (const auto &element : my_vector) {
         std::cout << element << " ";
      }
      std::cout << "\n";
   }
   void print_vector_mat  (std::vector<cv::Mat> my_vector) {

      for(auto &face: my_vector) {
         const double *row_pointer = face.ptr<double>(0);
         for(int i=0; i < dim; i++) {
            std::cout << row_pointer[i] << " ";
         }

         std::cout<<"next_face ";
      }

   }
   KNN knn_instance;
   std::vector<int> labels;
   std::vector<cv::Mat> num_reps;
   int dim;
   int num_people;
};
