#include <iostream>
#include <opencv2/core/mat.hpp>
// #include "cropimage.hpp"
// #include "Facedata.hpp"
// #include "rescale.hpp"
#include <knn.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/imgproc.hpp>
#include <random>
#include <knn_testing.hpp>
#include <vector>

int main() {
   

   int num_people = 50, dim = 3;
   KNN_Testing test_obj = KNN_Testing(num_people, dim);
   test_obj.test_clasify(num_people, dim);

}
