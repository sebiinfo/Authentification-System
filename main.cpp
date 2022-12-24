#include <iostream>

#include <opencv2/core/mat.hpp>
#include "cropimage.hpp"
#include "rescale.hpp"
#include "classification.hpp"
#include <random>

using namespace cv;

int main() {
    std::vector<Facedata> vect;
    for (int i = 0; i < 1000; i++) {
        Facedata data;
        data.id = i;
        Mat_<double> mat;
        mat.create(1, 50);
        for (int j = 0; j < 50; j++) {
            mat[0][j] = rand();
        }
        data.entries = mat;
        vect.push_back(data);
    }

    KNN algo(vect);
    std::cout << algo.classify(vect[465]) << std::endl;

}
