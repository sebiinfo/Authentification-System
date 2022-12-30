#include "fisher.hpp"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <string>

Fisher::Fisher(int num_people, int num_feature)
    : Vectorizer(num_people, num_feature) {
    load_images();
}

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

void Fisher::train(std::vector<cv::Mat> &images, std::vector<int> &labels) {
    cv::LDA lda(num_feature);
    lda.compute(images, labels);
}

void Fisher::load_images() {
    std::string filename, base_filename;
    for (int label = 1; label <= num_people; label++) {
        base_filename = "./" + std::to_string(label) + "/";
        for (int i = 1; i <= 9; i++) {
            filename = base_filename + std::to_string(i);
            filename = base_filename + ".pgm";
            cv::Mat image = cv::imread(base_filename, 0);
            cv::Mat flat_image = image.reshape(1, 1);
            images.push_back(flat_image);
            labels.push_back(label);
        }
    }
    for (int i = 0; i < labels.size(); i++) {
        std::cout << labels[i] << std::endl;
    }
}

int main() { Fisher f = Fisher(15, 10); }
