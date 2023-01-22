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
/* This class performs the Histograms of Oriented Gradients algorithm
 * The class has as attributes an image given as a Mat type; the
 * number_of_bins which the represents the number of different gradient
 * orientations that are considered when calculating the descriptor
 * and which is initialised by default as 9; the cell_size which
 * stores the width and the height of the cells that we form;
 * it is initialised as Size(8,8) since the division in 8x8 pixels
 * seems to be most efficient one - larger cell size will increase
 * spatial resolution but decrease the orientation resolution,
 * while smaller cell size will do the opposite
*/
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
