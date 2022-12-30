#include "fisher.hpp"
#include "vectorizer.cpp"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <string>

Fisher::Fisher(int num_people, int num_feature)
    : Vectorizer(num_people, num_feature) {
    load_images();
    lda = cv::LDA(num_feature);
    lda.compute(images, labels);
}

Fisher::~Fisher() {}

cv::Mat Fisher::normalize(cv::InputArray &src) {
    int channels = src.channels();
    cv::Mat out;
    if (channels == 1 || channels == 3) {
        cv::normalize(src, out, 0, 255, cv::NORM_MINMAX, channels);
    } else {
        src.copyTo(out);
    }
    return out;
}

void Fisher::load_images() {
    std::cout << "Loading Training Images" << std::endl;
    std::string filename, base_filename;
    for (int label = 1; label <= num_people; label++) {
        base_filename = "./yalefaces/train/" + std::to_string(label) + "/";
        for (int i = 1; i <= 9; i++) {
            filename = base_filename + std::to_string(i);
            filename = filename + ".png";
            cv::Mat image = cv::imread(filename);
            cv::Mat flat_image = image.reshape(1, 1);
            images.push_back(flat_image);
            labels.push_back(label);
        }
    }
    /* std::cout << "M = " << std::endl
              << " " << images[0] << std::endl
              << std::endl; */
    std::cout << "Finished Loading" << std::endl;
}

cv::Mat Fisher::vectorize(cv::Mat &image) { return lda.project(image); }

int main() { Fisher f = Fisher(15, 10); }
