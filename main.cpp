#include "classifier.hpp"
#include <cmath>
#include <iostream>
#include <opencv2/core/mat.hpp>
// #include "cropimage.hpp"
// #include "Facedata.hpp"
#include "rescale.hpp"
#include <knn.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/imgproc.hpp>
#include <random>
#include <knn_testing.hpp>
#include <decision_tree_testing.hpp>
#include <vector>
#include "model.hpp"


int main() {
   
   int num_people = 15, dim = 14;
//   KNN_Testing test_obj = KNN_Testing(num_people, dim);
//   test_obj.test_clasify(num_people, dim);

//   Testing_Decision_Tree::Testing_Build_Tree(num_people,dim) ;
//    Node *x=Testing_Node::create_node(num_people,dim);
//    Classifier *my_classifier = Testing_Decision_Tree::build_tree(num_people, dim);
//    std::vector<double> pula = {INFINITY, INFINITY, INFINITY};
//    cv::Mat query = cv::Mat(Testing_Functions::generate_random_vector(dim), true);
//    std::cout<<my_classifier->is_alienated(cv::Mat(pula));
//    Testing_Decision_Tree::Testing_Build_Tree(num_people, dim);
//    Testing_Node::print_node(x);
//    Testing_Functions::print_best_split(x->best_split);
    cv::Mat image = cv::imread("./yalefaces/test/11/2.png");

   // cv::Mat flat_image = image.reshape(1, 1);
    //cv::Mat flat_image = rescaleImage(image, 224, 224);
    //cv::imshow("a",flat_image);
    //cv::waitKey(0);
    Model model(num_people, dim, 224, 224, "Cascade", "Fisher", "KNN");
    std::cout << model.predict(image)[0] << std::endl;
   // Testing_Node::get_information_gain(x, {1,2,3});


}
