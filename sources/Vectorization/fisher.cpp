#include "fisher.hpp"
#include <opencv2/core/base.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>

cv::Mat Fisher::normalize(cv::InputArray src) {
    int channels = src.channels();
    cv::Mat out;
    if (channels == 1 || channels == 3) {
        cv::normalize(src, out, 0, 255, cv::NORM_MINMAX, channels);
    } else {
        src.copyTo(out);
    }
    return out;
}
