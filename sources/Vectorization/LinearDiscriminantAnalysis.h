#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/opencv.hpp>

class LinearDiscriminantAnalysis {
public:
    LinearDiscriminantAnalysis();

    LinearDiscriminantAnalysis(int num_components);

    cv::Mat get_eigenvects();

    cv::Mat get_eigenvals();

protected:

    cv::Mat eigenvals;
    cv::Mat eigenvects;
    int num_components;
};
