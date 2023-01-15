// #include "opencv2/face.hpp"
/* #include "vectorizer.hpp"

class CVFisher : public Vectorizer {
  public:
    CVFisher(int num_people, int num_feature)
        : Vectorizer(num_people, num_feature) {
        load_images();
        fisher_model = cv::face::FisherFaceRecognizer::create();
        fisher_model->train(images, labels);
    }
    int predict_label(const cv::Mat &image) {
        int predictedLabel = fisher_model->predict(image);
    }
    cv::Mat vectorize(cv::Mat &image) {
        cv::Mat W = fisher_model->getEigenVectors();
        return W.t() * image;
    }

  private:
    void load_images();
    cv::Ptr<cv::face::FisherFaceRecognizer> fisher_model;
    std::vector<cv::Mat> images;
    std::vector<int> labels;
    cv::Mat vectorized_images;
    int num_components;
    int dim;
}; */
