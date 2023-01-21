//The work for this code was shared equally by Cezara Petrui(cezarapetrui19) and Alexandru Serban (alexserban2002)

#include <opencv2/core.hpp>



#include <cstdio>
#include <iterator>




class HOG{

    public:

        HOG(cv::Mat image, int number_of_bins, int cell_width, int cell_height);

        ~HOG();







        std::vector<cv::Mat> compute_histograms(std::vector<cv::Mat> cells);

        std::vector<cv::Mat> normalize_histograms(std::vector<cv::Mat> histograms);




        cv::Mat image;


};
