#ifndef AUTHENTICATION_SYSTEM_KNN
#define AUTHENTICATION_SYSTEM_KNN

#include "Facedata.hpp"
#include "classifier.hpp"

class KNN : public Classifier {
  public:
    int k;

    KNN(std::vector<Facedata> data);

    static bool compare(const Facedata &v1, const Facedata &v2);

    int classify(const Facedata &query);

  private:
    double compute_distance(Facedata query,
                            int i); // computes Euclidian distance between a
    // query and ith vector in data
};

#endif
