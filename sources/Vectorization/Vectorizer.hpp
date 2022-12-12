#include <opencv2/core.hpp>

class Vectorizer {
    /*
    A base class for different vectorization methods that would be implement
    */
public:
    Vectorizer(int num_people, int num_feature);
    ~Vectorizer();

    std::array<float> vectorize(cv::Mat image, std::array<cv::Rect> faces);
    std::array<float> vectorize(cv::Mat image);
    void vectorize_update(cv::Mat image, std::array<cv::Rect> faces, std::vector<std::vector<float>> numerical_reps);
    void vectorize_update(cv::Mat image, std::vector<std::vector<float>> numerical_reps);

    int num_people;
    int num_feature;

};