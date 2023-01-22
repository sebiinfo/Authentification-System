#include "classifier.hpp"
#include "knn_testing.hpp"
#include <math.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <set>

static void debug_print(cv::Mat temp) {
    std::cout << "temp.dims = " << temp.dims << " temp.size = [";
    for (int i = 0; i < temp.dims; ++i) {
        if (i)
            std::cout << " X ";
        std::cout << temp.size[i];
    }
    std::cout << "] temp.channels = " << temp.channels() << std::endl;
}

Classifier::Classifier(int num_people, int dim) {

    this->num_people = num_people;
    this->dim = dim;
}

Classifier::Classifier(int num_people, int dim, std::vector<cv::Mat> &num_reps,
                       std::vector<int> &labels) {
    this->num_people = num_people;
    this->dim = dim;

    if (num_reps.size() != labels.size()) {
        throw std::length_error(
            "vectors of characteristics and ids have different lengths");
    }

    this->num_reps = num_reps;
    this->labels = labels;
}

void Classifier::train(std::vector<cv::Mat> &num_reps,
                       std::vector<int> &labels) {

    this->num_reps = num_reps;
    this->labels = labels;
}

int Classifier::classify(const cv::Mat &image) { return 0; }

Classifier::~Classifier() = default;

double Classifier::compute_distance(const cv::Mat &mat1,
                                    const cv::Mat &mat2) const {
    double sum = 0;
    for (int cont = 0; cont < dim; ++cont) {
        sum += pow(mat1.at<double>(0, cont) - mat2.at<double>(0, cont), 2);
    }
    return sqrt(sum);
}

bool Classifier::is_alienated_id_normal(const cv::Mat &query, int id) {
    //    std::cout << std::endl << "id: " << id << "\n";
    //    for (int i = 0; i < dim; ++i) {
    //        std::cout << query.at<double>(0, i) << " ";
    //    }
    //    std::cout << "\n";
    // contains on position i the sum of the faces on coordinate i
    std::vector<double> averages;
    // contains the empirical variance of faces on coordinate i
    std::vector<double> variances;
    // hold the number of people with id
    int num_people_id = 0;
    for (int i = 0; i < labels.size(); ++i) {
        if (labels[i] == id) {
            num_people_id++;
        }
    }
    //    std::cout << "  num_poeple_id = " << num_people_id << "\n";

    if (num_people_id == 0) {
        std::cout << "\n Labels for which the function is_alienated id was "
                     "called wrongfully: \n";
        for (auto i : labels) {
            std::cout << i << " ";
        }
        std::cout << "\n the id is: " << id << "\n";
        std::cout << "num_people is " << num_people << "\n";
        std::cout << "labels size is " << labels.size() << "\n";
        std::cout << "num_reps size is " << num_reps.size() << "\n";
        throw std::invalid_argument(
            "function is_alienated_id called for a non-existent id");
    }

    // now we compute the empirical averages and variance
    for (int entry = 0; entry < dim; ++entry) {
        double average_entry = 0;
        double variance_entry = 0;

        for (int i = 0; i < num_reps.size(); ++i) {
            if (labels[i] == id) { // check if the person has label id
                average_entry += num_reps[i].at<double>(0, entry);
                variance_entry += pow(num_reps[i].at<double>(0, entry), 2);
            }
        }
        averages.push_back(average_entry / num_people_id);

        // we use that the empirical variance is 1/num_people*sum(x_i^2)-
        // (empirical average)^2
        variances.push_back(variance_entry / num_people_id -
                            (pow(averages[entry], 2)));
    }
    //    std::cout << " Averages are:\n";
    //    for (auto a : averages) {
    //        std::cout << " " << a << " ";
    //    }
    //    std::cout << "\n Variances are:\n";
    //    for (auto v : variances) {
    //        std::cout << " " << v << " ";
    //    }

    for (double var : variances) {
        if (var < -pow(10, -4)) {
            throw std::domain_error(
                "all the variances should have been positive");
        }
    }
    // now we have the empirical mean and variances and want to test if query is
    // in the 95% confidence interval

    // we keep count of the number of coordinates on which the query in
    // alienated
    int count_alienated_id = 0;

    for (int entry = 0; entry < dim; ++entry) {
        if (query.at<double>(0, entry) <
                averages[entry] - 1.96 * sqrt(variances[entry]) * 2 ||
            query.at<double>(0, entry) >
                averages[entry] + 1.96 * sqrt(variances[entry]) * 2) {
            // we increase the number of alienated coordinates
            count_alienated_id++;
        }
    }
    //    std::cout << "\n"
    //              << "count_alienated_id is: " << count_alienated_id;
    //    std::cout << "\n The answer for this id is "
    //              << (double(count_alienated_id) / dim > alienation_constant)
    //              << "\n";
    return double(count_alienated_id) / dim > alienation_constant;
}

bool Classifier::is_alienated_id_linear(const cv::Mat &query, int id) {
    // we want to compute the max distance between any two reps of label id
    std::vector<cv::Mat> num_reps_id;
    for (int i = 0; i < labels.size(); ++i) {
        if (labels[i] == id) {
            num_reps_id.push_back(num_reps[i]);
        }
    }
    double distance = 0;
    for (int i = 0; i < num_reps_id.size(); ++i) {
        for (int j = i + 1; j < num_reps_id.size(); ++j) {
            double distance_ij =
                compute_distance(num_reps_id[i], num_reps_id[j]);
            //            if (distance_ij>max_distance){
            //                max_distance=distance_ij;
            //            }
            distance += distance_ij;
        }
    }
    distance = distance / double(num_reps_id.size());
    std::vector<double> gravity_center;
    for (int i = 0; i < dim; ++i) {
        double coord_i = 0;
        for (auto rep : num_reps_id) {
            coord_i += rep.at<double>(0, i);
        }
        gravity_center.push_back(coord_i / double(num_reps_id.size()));
    }

    return compute_distance(cv::Mat(gravity_center, true), query) >
           distance * 1.5;

    //    for (auto & rep : num_reps_id){
    //        if (compute_distance(query, rep)>0.8*max_distance){
    //            return true; //it is alienated
    //        }
    //    }
    // return double(count_alienated)/double
    // (num_reps_id.size())>alienation_constant;
    return false;
}

bool Classifier::is_alienated(const cv::Mat &query) {
    /*We assume that the distribution of the numerical representations of a
     * person are a random variable distributed around a point in the dim
     * dimensional space. We want to look at all the points that we have for
     * each label and compute and estimator. Afterwards we check if the query is
     * in the 95% confidence interval or the groups of any label, if not we
     * return true
     */

    cv::Size s;
    //    std::cout << "num_people: " << num_people << " dim= " << dim;
    ////    s = num_reps[0].size();
    ////    std::cout << "\n num_reps is : \n" << &s;
    ////    debug_print(num_reps[0]);
    //    // KNN_Testing::print_vector_mat(num_reps);
    //    std::cout << "\n The labels are:  ";
    //    for (auto i:labels){
    //        std::cout<<i<<" ";
    //    }
    //    KNN_Testing::print_vector(labels);
    //    std::cout << "\n";
    std::set<int> id_set;

    for (int i = 0; i < labels.size(); ++i) {
        id_set.insert(labels[i]);
    }
    for (auto id : id_set) {
        if (!is_alienated_id_normal(query, id)) {
            // if it is not alienated by the faces with label id, then it is not
            // alienated in general, so the query might be the person with the
            // label id
            return false;
        }
    }

    // in case we didn't return false we return true because we are alienated by
    // everyone
    return true;
}
