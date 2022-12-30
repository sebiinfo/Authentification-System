#include "fisher.hpp"
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>

Fisher::Fisher(int num_people, int num_feature)
    : Vectorizer(num_people, num_feature) {
        load_images();
        lda = cv::LDA(num_feature);
        lda.compute(images, labels);
    }

Fisher::~Fisher() {}

cv::Mat Fisher::normalize(cv::InputArray & src) {
    int channels = src.channels();
    cv::Mat out;
    if (channels == 1 || channels == 3) {
        cv::normalize(src, out, 0, 255, cv::NORM_MINMAX, channels);
    } else {
        src.copyTo(out);
    }
    return out;
}

cv::Mat Fisher::vectorize(cv::Mat & image) {
    return lda.project(image);
}