
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include "knn_testing.hpp"

KNN_Testing::KNN_Testing(int num_people , int dim) {
   this->num_people = num_people; 
   this->dim = dim;
   this->labels = generate_random_id(num_people);
   this->num_reps = generate_faces(num_people, dim);
   this->knn_instance = KNN(num_people, dim, num_reps, labels);
}

std::vector<double> KNN_Testing::generate_random_vector(int dim) {
   // Generates a random line vector with varialble size
   std::random_device rd;
   auto seed = std::chrono::system_clock::now().time_since_epoch().count();
   std::mt19937 gen (seed);
   std::uniform_real_distribution<> dis(0, 10.0);

   std::vector<double> result(dim);

   for (int i=0;i < result.size();i++) {
      result[i] = dis(gen);
   }
   return result;
}

std::vector<int> KNN_Testing::generate_random_id(int num_people) {
   // generates a random list of ids corresponding to a vector of faces
   std::vector<int> result(num_people);

   for (auto &face : result) {
      face = rand() % 10000;
      face = face % 4;
   }

   return result;
}

std::vector<cv::Mat> KNN_Testing::generate_faces(int num_people, int dim) {
   // generates faces from line_vectors
   std::vector<cv::Mat> faces_vector(num_people);

   for (auto &face : faces_vector) {
      face = cv::Mat(generate_random_vector(dim), true);
   }

   return faces_vector;
}

void KNN_Testing::test_clasify(int number_faces, int dim) {

   cv::Mat query = cv::Mat(generate_random_vector(dim));
   std::cout<<"  Query is :" << query.at<double>(0,0)<<" "<<query.at<double>(0,1)<< "\n";
   print_vector(knn_instance.labels);
   std::cout<<"\n";
   print_vector_mat(knn_instance.num_reps);
   std::cout<<"\n\n\n";

   // Will it print a cv::Mat? We'll find out :)
   std::cout <<"\n "<<" This is the answer: " <<knn_instance.classify(query)<<" \n";

   print_vector(knn_instance.labels);
   std::cout<<"\n";
   print_vector_mat(knn_instance.num_reps);
}

