#include "knn.hpp"
#include <exception>
#include <map>
#include <numeric>
#include <opencv2/core/mat.hpp>
#include <random>
#include <vector>

// Creates a comparator object that will help us with sorting using a
// non-static function
struct compareFunctor {
    explicit compareFunctor(KNN *knn_current_object)
        : knn_current_object(knn_current_object) {}

    bool operator()(const cv::Mat &v1, const cv::Mat &v2) const {
        return knn_current_object->compare(v1, v2);
    }

    KNN *knn_current_object;
};

// When sorting the numerical representation we also need information for the
// labels vector.Gathering the sorting permutation solves this problem

std::vector<int> get_permutation_vector(std::vector<cv::Mat> &sort_vector,
                                        compareFunctor comparator) {
    std::vector<int> permutation_vector(sort_vector.size());
    std::iota(permutation_vector.begin(), permutation_vector.end(), 0);

    std::sort(permutation_vector.begin(), permutation_vector.end(),
              [&](int i, int j) {
                  return comparator(sort_vector[i], sort_vector[j]);
              });

    return permutation_vector;
}

template <typename T>
void apply_permutation(std::vector<int> &permutation_vector,
                       std::vector<T> &my_vector) {
    std::vector<bool> done(permutation_vector.size());

    for (int i = 0; i < permutation_vector.size(); i++) {
        if (done[i])
            continue;

        int previous_position = i;
        int correct_position = permutation_vector[i];

        while (i != correct_position) {
            std::swap(my_vector[previous_position],
                      my_vector[correct_position]);

            done[correct_position] = true;
            previous_position = correct_position;
            correct_position = permutation_vector[correct_position];
        }
    }
}

// KNN_Testing Object for easy testing of fuctions

KNN::KNN(int num_people, int dim) : Classifier(num_people, dim) {

    //!!!! DOES NOT INITIALIZE k HERE THE RIGHT WAY
    this->num_people = num_people;
    this->k = int(sqrt(num_people));
    this->dim = dim;
}

/* void KNN::train(std::vector<cv::Mat> &num_reps,
                       std::vector<int> &labels) {
    this->num_reps = num_reps;
    this->labels = labels;
} */

KNN::KNN(int num_people, int dim, std::vector<cv::Mat> &num_reps,
         std::vector<int> &labels)
    : Classifier(num_people,dim,num_reps, labels) {
    this->num_people = num_people;
    this->dim = dim;
    this->num_reps=num_reps;
    this->labels=labels;
    this->k = int(sqrt(num_reps.size()));
}

double KNN::compute_distance(cv::Mat vect) const {
    // todo check weather we need a weigthed sum or different weight
    double sum = 0;

    for (int cont = 0; cont < dim; ++cont) {
        sum += pow(query.at<double>(0, cont) - vect.at<double>(0, cont), 2);
    }

    return sqrt(sum);
}

bool KNN::compare(const cv::Mat &v1, const cv::Mat &v2) {
    return (compute_distance(v1) < compute_distance(v2));
}

int KNN::classify(const cv::Mat &query) {
    this->query = query;

    // we check if the query is too far off from our data
    if (is_alienated(query)) {
        return -1;
    }
//    std::cout<<"labels are: \n";
//    for (auto i: labels){
//        std:: cout<< i<<" ";
//    }
//    std::cout<<"\n";
    // now we want to sort the data in terms of the distance, O(nlogn),

    std::vector<int> permutation_numerical_faces =
        get_permutation_vector(num_reps, compareFunctor(this));

    apply_permutation(permutation_numerical_faces, this->labels);
    apply_permutation(permutation_numerical_faces, this->num_reps);
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

    //Now we check if we have a false positive
    if (is_alienated_id(query, max_id)){
        return -1;
    }
    return max_id;
}

KNN::~KNN() {
    query.release();

    for (auto representation : num_reps) {
        representation.release();
    }

    num_reps.clear();
    labels.clear();
}

// KNN testing
