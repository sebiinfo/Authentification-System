#include "classifier.hpp"

#include <bits/stdc++.h>
#include <math.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <set>

Classifier::Classifier(int num_people, int dim) {
   // if (data[0].entries.rows > 1) {
   //   throw "data has wrong dimensions";
   //}
   this->num_people = num_people;
   this->dim = dim;
}

Classifier::Classifier(int num_people, int dim, std::vector<cv::Mat> &num_reps,
                       std::vector<int> &labels) {
   this->num_people = num_people;
   this->dim = dim;

   if (num_reps.size() != labels.size()) {
      throw std::length_error("vectors of characteristics and ids have different lengths");
   }

   this->num_reps = num_reps;
   this->labels = labels;
}


void Classifier::train(std::vector<cv::Mat> &num_reps,
                       std::vector<int> &labels) {
   this->num_reps = num_reps;
   this->labels = labels;
}

int Classifier::classify(cv::Mat &image) {return 0;}

Classifier::~Classifier() = default;

bool Classifier::is_alienated_id(const cv::Mat &query, int id) {

    // contains on position i the sum of the faces on coordinate i
    std::vector <double> averages;
    //contains the empirical variance of faces on coordinate i
    std::vector <double> variances;
    // hold the number of people with id
    int num_people_id;
    for (int i=0; i<num_people; ++i){
        if (labels[i]==id){
            num_people_id++;
        }
    }

    if (num_people_id==0){
        throw std::invalid_argument("function is_alienated_id called for a non-existent id");
    }

    //now we compute the empirical averages and variance
    for (int entry=0;entry <dim; ++entry){
        double average_entry=0;
        double variance_entry=0;

        for (int i=0; i<num_people; ++i){
            if (labels[i]==id) { //check if the person has label id
                average_entry+=num_reps[i].at<double>(0, entry);
                variance_entry+=pow(num_reps[i].at<double>(0, entry),2);
            }
        }
        averages.push_back(average_entry/num_people_id);

        // we use that the empirical variance is 1/num_people*sum(x_i^2)- (empirical average)^2
        variances.push_back(variance_entry/num_people_id-(pow(averages[entry],2)));
    }

    for( double var: variances){
        if(var<0){
            throw std::domain_error("all the variances should have been positive");
        }
    }
    //now we have the empirical mean and variances and want to test if query is in the 95% confidence interval

    //we keep count of the number of coordinates on which the query in alienated
    int count_alienated_id=0;


    for (int entry=0; entry<dim; ++entry){
        if(query.at<double>(0,entry)<averages[entry]-1.96*sqrt(variances[entry])
        || query.at<double>(0,entry)>averages[entry]+1.96*sqrt(variances[entry])){
            //we increase the number of alienated coordinates
            count_alienated_id++;
        }
    }

        return double(count_alienated_id)/num_people_id>alienation_constant;

}

bool Classifier::is_alienated(const cv::Mat& query) {
/*We assume that the distribution of the numerical representations of a person are a random variable distributed around
 * a point in the dim dimensional space. We want to look at all the points that we have for each label and compute and estimator.
 * Afterwards we check if the query is in the 95% confidence interval or the groups of any label, if not we return true
 */

std::set <int> id_set;

for (int i=0; i<num_people; ++i){
    id_set.insert(labels[i]);
}
for (auto id: id_set) {
    if (!is_alienated_id(query, id)) {
// if it is not alienated by the faces with label id, then it is not alienated in general, so
// the query might be the person with the label id
        return false;
    }
}

//in case we didn't return false we return true because we are alienated by everyone
return true;


}

