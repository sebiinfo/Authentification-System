//The work for this code was shared equally by Cezara Petrui(cezarapetrui19) and Alexandru Serban (alexserban2002)

#include "HOG.hpp"


HOG::HOG(cv::Mat image, int number_of_bins=9, int cell_width=8, int cell_height=8){
    this -> image = image;
    this -> number_of_bins = number_of_bins;
    cell_size = cv::Size(cell_width,cell_height);
}


HOG::~HOG()=default;


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
