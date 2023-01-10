#include <iostream>
#include <opencv2/core/mat.hpp>
// #include "cropimage.hpp"
// #include "Facedata.hpp"
// #include "rescale.hpp"
#include <knn.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/imgproc.hpp>
#include <random>
#include <vector>

std::vector<double> generate_random_vector(int size) {
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_real_distribution<> dis(0, 1.0);

   std::vector<double> result(size);

   for (auto &element : result) {
      element = dis(gen);
   }
   return result;
}
std::vector<int> generate_random_id(int number_faces) {
   std::vector<int> result(number_faces);

   for (auto &face : result) {
      face = rand() % 10000;
   }

   return result;
}

std::vector<cv::Mat> generate_faces(int number_faces, int size) {
   std::vector<cv::Mat> faces_vector(number_faces);

   for (auto &face : faces_vector) {
      face = cv::Mat(generate_random_vector(size));
   }

   return faces_vector;
}

int main() {
   // Please use testing functions from the test directory

   std::vector<cv::Mat> num_faces = generate_faces(5, 1);
   std::vector<int> labels = generate_random_id(5);

   KNN my_KNN = KNN(5, 1, num_faces, labels);

   cv::Mat query = cv::Mat(generate_random_vector(1));
   std::cout<<my_KNN.classify(query);

   return 0;
}
