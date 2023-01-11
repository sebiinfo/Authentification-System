#ifndef AUTHENTICATION_SYSTEM_KNN
#define AUTHENTICATION_SYSTEM_KNN

#include <iostream>
#include <opencv2/core/mat.hpp>
#include <vector>

#include "classifier.hpp"

class KNN : public Classifier {
 public:
   int k;

   KNN(int num_people, int dim, std::vector<cv::Mat> &num_reps,
       std::vector<int> &labels);

   bool compare(const cv::Mat &v1, const cv::Mat &v2);

   virtual int classify(const cv::Mat &query);

   // computes Euclidian distance between a
   double compute_distance(cv::Mat vect) const;

   int dim;
   int num_people;
   cv::Mat query;
   std::vector<cv::Mat> num_reps;
   std::vector<int> labels;
   ~KNN();
   // query and ith vector in data
};

class KNN_Testing {
 public:
   KNN_Testing(KNN knn_instance) : knn_instance(knn_instance) {}
   std::vector<double> generate_random_vector(int size) ;
   std::vector<int> generate_random_id(int number_faces);
   std::vector<cv::Mat> generate_faces(int number_faces, int size);
   void test_clasify(int number_faces, int size); 
    
   template<typename T>
   void print_vector(std::vector<T> my_vector){
       for(const auto &element:my_vector) {
           std::cout<<element;
       }
   }
   KNN knn_instance;
};
#endif
