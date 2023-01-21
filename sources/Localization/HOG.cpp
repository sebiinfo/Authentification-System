//The work for this code was shared equally by Cezara Petrui(cezarapetrui19) and Alexandru Serban (alexserban2002)

#include "HOG.hpp"


HOG::HOG(cv::Mat image, int number_of_bins=9, int cell_width=8, int cell_height=8){
    this -> image = image;
    this -> number_of_bins = number_of_bins;
    cell_size = cv::Size(cell_width,cell_height);
}


HOG::~HOG()=default;


cv::Mat HOG::convert_to_grayscale(){
    cv::Mat gray;
    cvtColor(image, gray, cv::COLOR_RGB2GRAY);
    return gray;
}


void HOG::compute_gradient(cv::Mat grad_x, cv::Mat grad_y) {
    Sobel(image, grad_x, CV_32F, 1, 0);
    Sobel(image, grad_y, CV_32F, 0, 1);
}


std::vector<cv::Mat> HOG::divide_into_cells(cv::Mat img){
    std::vector<cv::Mat> cells;
    for (int y = 0; y < img.rows; y += cell_size.height) {
        for (int x = 0; x < img.cols; x += cell_size.width) {
            cv::Rect cell_roi(x, y, cell_size.width, cell_size.height);
            cv::Mat cell = img(cell_roi);
            cells.push_back(cell);
        }
    }
    return cells;
}


std::vector<cv::Mat> HOG::compute_histograms(std::vector<cv::Mat> cells){
    std::vector<cv::Mat> histograms;
    for (cv::Mat cell : cells) {
        cv::Mat hist = cv::Mat::zeros(1, number_of_bins, CV_32F);
        for (int i = 0; i < cell.rows; i++) {
            for (int j = 0; j < cell.cols; j++) {
                int bin = (int)(cell.at<float>(i, j) / 180 * number_of_bins);
                hist.at<float>(0, bin)++;
            }
        }
        histograms.push_back(hist);
    }
    return histograms;
}


std::vector<cv::Mat> HOG::normalize_histograms(std::vector<cv::Mat> histograms){
    std::vector<cv::Mat> normalized_histograms;
    for (cv::Mat hist : histograms) {
        cv::Mat normalized_hist;
        normalize(hist, normalized_hist, 1, 0, cv::NORM_L2);
        normalized_histograms.push_back(normalized_hist);
    }
    return normalized_histograms;
}


cv::Mat HOG::hog_descriptor(){
    cv::Mat gray = convert_to_grayscale();
    cv::Mat grad_x, grad_y;
    compute_gradient(grad_x, grad_y);
    cv::Mat angle, mag;
    cartToPolar(grad_x, grad_y, mag, angle, true);
    std::vector<cv::Mat> cells = divide_into_cells(angle);
    std::vector<cv::Mat> histograms = compute_histograms(cells);
    std::vector<cv::Mat> normalized_histograms = normalize_histograms(histograms);
    cv::Mat descriptor;
    hconcat(normalized_histograms, descriptor);
    return descriptor;
}
