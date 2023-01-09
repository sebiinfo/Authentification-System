#include "knn.hpp"

#include <map>
#include <opencv2/core/mat.hpp>
#include <vector>

struct compareFunctor {
   explicit compareFunctor(KNN *knn_current_object)
       : knn_current_object(knn_current_object) {}
   bool operator()(const cv::Mat &v1, const cv::Mat &v2) const {
      return knn_current_object->compare(v1, v2);
   }
   KNN *knn_current_object;
};
KNN::KNN(int num_people, int dim, std::vector<cv::Mat> &num_reps,
         std::vector<int> &labels)
    : Classifier(num_people, dim, num_reps, labels) {
    this->dim= dim;
    this->num_reps= num_reps;
    this->num_people=num_people;
    this->labels=labels;
    this-> k = int(sqrt(num_people));
}

double KNN::compute_distance(cv::Mat vect) const {
   // todo check weather we need a weigthed sum or different weight
   double sum = 0;
   for (int cont = 0; cont < dim; ++cont) {
      sum += pow(query.at<double>(0, cont) - vect.at<double>(0, cont), 2);
   }
   return sqrt(sum);
}

bool KNN::compare(const cv::Mat &v1, const cv::Mat &v2) const {
   return (compute_distance(v1) < compute_distance(v2));
}

int KNN::classify(const cv::Mat &query) {
   // first we store in the distance_to_query field of the struct the right
   // distance
   this->query = query;
   // now we want to sort the data in terms of the distance, O(nlogn),
   // n-dimensional trees will maybe be implemented later (O(n))
   std::sort(num_reps.begin(), num_reps.end(), compareFunctor(this));

   std::map<int, int> id_freq;
   for (int i = 0; i < k; ++i) {
      // if the id has appeared before in the map
      if (id_freq.count(labels[i])) {
         id_freq[labels[i]] += 1;
      } else {
         id_freq[labels[i]] = 1;
      }
   }
   int max_freq = 0, max_id;
   for (auto &it : id_freq) {
      if (it.second > max_freq) {
         max_id = it.first;
         max_freq = it.second;
      }
   }
   return max_id;
}

KNN::~KNN(){
   query.release();

   for(auto representation: num_reps) {
      representation.release();
   }
   num_reps.clear();
   labels.clear();
}
