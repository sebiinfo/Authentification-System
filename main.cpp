#include <iostream>

#include <opencv2/core/mat.hpp>
using namespace std;
using namespace cv;
int main() {
    int dim[1] = {3};
    Mat M(7, 7, CV_32FC2, Scalar(1, 3));
    // cout<<M;
    cv::Mat_<float> x;
    cout << "Hello World!" << endl;
    return 0;

}
