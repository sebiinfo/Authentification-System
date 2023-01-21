#include "classifier.hpp"
#include <cmath>
#include <iostream>
#include <opencv2/core/mat.hpp>
// #include "cropimage.hpp"
// #include "Facedata.hpp"
#include "model.hpp"
#include "rescale.hpp"
#include <decision_tree_testing.hpp>
#include <fisher.hpp>
#include <knn.hpp>
#include <knn_testing.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/imgproc.hpp>
#include <random>
#include <vector>

int main() {

    int num_people = 15, dim = 14;
    std::cout << "Creating the Model\n";
    Model model(num_people, dim, 0, 0, "", "Fisher", "KNN");
    std::cout << "Created the Model\n";

       Testing_Decision_Tree::Testing_Build_Tree(num_people,dim) ;
        Node *x=Testing_Node::create_node(num_people,dim);
        Classifier *my_classifier =
        Testing_Decision_Tree::build_tree(num_people, dim);

    cv::Mat image_test;
    int positives, obtained_label;
    std::string filename, base_filename;
    for (int label = 1; label <= num_people; label++) {
        base_filename =
            "./resources/yalefaces/test/" + std::to_string(label) + "/";
        for (int i = 1; i <= 2; i++) {
            filename = base_filename + std::to_string(i);
            filename = filename + ".png";
            image_test = cv::imread(filename);
            image_test = image_test.reshape(1, 1);
            obtained_label = model.predict(image_test)[0];
             std::cout << "The obtained label was: " << obtained_label
                      << " while the expected was: " << label << std::endl;
            positives += obtained_label == label;
        }
    }
    std::cout << "\n\n The final statistics are: " << positives << " out of "
              << 2 * num_people;

    //    cv::Mat image = cv::imread("./yalefaces/test/2/2.png");
    //    cv::Mat flat_image = image.reshape(1, 1);
    // std::cout << model.predict(flat_image)[0] << std::endl;

    // full_test_fisher();
    //   KNN_Testing test_obj = KNN_Testing(num_people, dim);
    //   test_obj.test_clasify(num_people, dim);

    //   Testing_Decision_Tree::Testing_Build_Tree(num_people,dim) ;
    //    Node *x=Testing_Node::create_node(num_people,dim);
    //    Classifier *my_classifier =
    //    Testing_Decision_Tree::build_tree(num_people, dim);
    //    std::vector<double> pula = {INFINITY, INFINITY, INFINITY};
    //    cv::Mat query =
    //    cv::Mat(Testing_Functions::generate_random_vector(dim), true);
    //    std::cout<<my_classifier->is_alienated(cv::Mat(pula));
    //    Testing_Decision_Tree::Testing_Build_Tree(num_people, dim);
    //    Testing_Node::print_node(x);
    //    Testing_Functions::print_best_split(x->best_split);
    // Model model(num_people, dim, 224, 224, "Cascade", "Fisher", "KNN");

    // cv::Mat flat_image = image.reshape(1, 1);
    // cv::Mat flat_image = rescaleImage(image, 224, 224);
    // cv::imshow("a",flat_image);
    // cv::waitKey(0);
    // Testing_Node::get_information_gain(x, {1,2,3});
}