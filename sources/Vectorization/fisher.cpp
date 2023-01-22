#include "fisher.hpp"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <string>

#include "vectorizer.hpp"

static void debug_print(cv::Mat temp) {
    std::cout << "temp.dims = " << temp.dims << " temp.size = [";
    for (int i = 0; i < temp.dims; ++i) {
        if (i)
            std::cout << " X ";
        std::cout << temp.size[i];
    }
    std::cout << "] temp.channels = " << temp.channels() << std::endl;
}

static cv::Mat formatImagesForPCA(const std::vector<cv::Mat> &data) {
    // cv::Mat dst(static_cast<int>(data.size()), data[0].rows * data[0].cols,
    // CV_32F);
    cv::Mat dst(data.size(), data[0].rows * data[0].cols, CV_32F);
    for (unsigned int i = 0; i < data.size(); i++) {
        cv::Mat image_row = data[i].clone().reshape(1, 1);
        // cv::Mat row_i = dst.row(i);
        image_row.convertTo(dst.row(i), CV_32F);
    }
    return dst;
}
static void print_dims(cv::Mat m) {
    int nDims = m.dims;
    std::cout << nDims << ": " << std::endl;
    for (int i = 0; i < nDims; i++) {
        std::cout << m.size[i] << " ";
    }
    std::cout << "----------------------" << std::endl;
}

Fisher::Fisher(int num_people, int num_feature)
    : Vectorizer(num_people, num_feature) {}

Fisher::Fisher(int num_people, int num_feature, std::vector<cv::Mat> &images,
               std::vector<int> &labels)
    : Fisher(num_people, num_feature) {
    this->train(images, labels);
}

void Fisher::train(std::vector<cv::Mat> &train_images,
                   std::vector<int> &train_labels) {
    int dim = images.size();
    cv::Mat train_data = formatImagesForPCA(train_images);
    /* std::cout << "R (python)  = " << std::endl
              << format(train_data, cv::Formatter::FMT_PYTHON) << std::endl
              << std::endl; */
    pca =
        cv::PCA(train_data, cv::Mat(), cv::PCA::DATA_AS_ROW, dim - num_people);
    /* std::cout << "Mean->" << pca.mean.empty() << " Eigen-> "
              << pca.eigenvectors.empty() << " Rows-> " << pca.mean.rows
              << " Cols-> " << pca.mean.cols << std::endl; */
    // std::cout << "Created PCA" << std::endl;
    /* std::cout << "This is the first projection I get "
              << pca.project(train_images[0]) << std::endl; */
    cv::Mat projected_pca_data = pca.project(train_data);
    lda = cv::LDA(num_feature);
    lda.compute(projected_pca_data, train_labels);
    // std::cout << "Created LDA" << std::endl;
    std::cout << lda.project(projected_pca_data.row(0)) << std::endl;
    for (auto &image : train_images) {
        image = vectorize(image);
    }
    // vectorize_trainset();
}

cv::Mat Fisher::vectorize(const cv::Mat &image) {
    cv::Mat output = pca.project(image);
    return lda.project(output);
}

int Fisher::predict_label(const cv::Mat &projection) {
    double min_dist = DBL_MAX;
    int best_guess = -1;
    for (int i = 0; i < dim; i++) {
        double dist =
            cv::norm(projection, vectorized_images.row(i), cv::NORM_L2);
        if (min_dist > dist) {
            min_dist = dist;
            best_guess = labels[i];
        }
    }
    return best_guess;
}

void load_tests(std::vector<cv::Mat> &images_test,
                std::vector<int> &expected_labels, int num_people) {
    std::cout << "Loading Testing Images" << std::endl;
    std::string filename, base_filename;
    for (int label = 1; label <= num_people; label++) {
        base_filename = "./yalefaces/test/" + std::to_string(label) + "/";
        for (int i = 1; i <= 2; i++) {
            filename = base_filename + std::to_string(i);
            filename = filename + ".png";
            cv::Mat image = cv::imread(filename);
            cv::Mat flat_image = image.reshape(1, 1);
            /* int rows = flat_image.rows;
            int cols = flat_image.cols;
            std::cout << rows << ", " << cols << std::endl; */
            images_test.push_back(flat_image);
            expected_labels.push_back(label);
        }
    }
    std::cout << "Finished Loading Tests" << std::endl;
}

void test_fisher(Fisher &F) {
    std::vector<cv::Mat> images_test;
    std::vector<int> expected_labels;
    load_tests(images_test, expected_labels, F.num_people);
    cv::Mat formated_images_test = formatImagesForPCA(images_test);
    print_dims(formated_images_test);
    // Breaks here.
    cv::Mat projection = F.pca.project(formated_images_test);
    projection = F.lda.project(projection);
    int guess;
    for (int i = 0; i < images_test.size(); i++) {
        std::cout << i + 1 << " ";
        guess = F.predict_label(projection.row(i));
        if (guess != expected_labels[i]) {
            std::cout << "For testing image " << i << "the guess was " << guess
                      << "while the expected label was " << expected_labels[i];
        }
        std::cout << std::endl;
    }
}

void full_test_fisher() {
    int num_people = 15, dim = 14;
    std::vector<cv::Mat> train_images;
    std::vector<int> train_labels;
    std::cout << "Loading Training Images" << std::endl;
    std::string filename, base_filename;
    for (int label = 1; label <= num_people; label++) {
        base_filename = "./yalefaces/train/" + std::to_string(label) + "/";
        for (int i = 1; i <= 9; i++) {
            filename = base_filename + std::to_string(i);
            filename = filename + ".png";
            cv::Mat image = cv::imread(filename);
            cv::Mat flat_image = image.reshape(1, 1);
            train_images.push_back(flat_image);
            train_labels.push_back(label);
        }
    }
    std::cout << "Finished Loading" << std::endl;
    Fisher f(num_people, dim);
    f.train(train_images, train_labels);
    test_fisher(f);
}

/* int main() {
    Fisher f = Fisher(15, 14);
    std::cout << "starting to test" << std::endl;
    test_fisher(f);
} */
