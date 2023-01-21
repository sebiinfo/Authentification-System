//The work for this code was shared equaly by Cezara Petrui(cezarapetrui19) and Alexandru Serban (alexserban2002)

#include "localizer.cpp"
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/base.hpp>

#include <cstdio>
#include <iterator>
#include <limits>



class HOG{

    public:

        HOG(cv::Mat image, int number_of_bins, int cell_width, int cell_height);

        ~HOG();

        cv::Mat convert_to_grayscale();

        void compute_gradient(cv::Mat grad_x, cv::Mat grad_y);

        std::vector<cv::Mat> divide_into_cells(cv::Mat img);

        std::vector<cv::Mat> compute_histograms(std::vector<cv::Mat> cells);

        std::vector<cv::Mat> normalize_histograms(std::vector<cv::Mat> histograms);

        cv::Mat hog_descriptor();


        cv::Mat image;
        int number_of_bins;
        cv::Size cell_size;

};
