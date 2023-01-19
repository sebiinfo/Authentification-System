#ifndef AUTHENTICATION_SYSTEM_LOCALIZER_HPP
#define AUTHENTICATION_SYSTEM_LOCALIZER_HPP

#include <opencv2/core/mat.hpp>

class Localizer {
  public:
    // Initialize localiser with height = 244, width = 244
    Localizer();

    // Initialize localiser with height = w, width = w
    Localizer(int w,int padd);

    // Initialize localiser with height = h, width = w and pad
    Localizer(int w, int h, int pad);

    // Deconstructor
    ~Localizer();

    // Update array faces by replacing it with faces detected on the image
    virtual void localize_rect(cv::Mat & image, std::vector<cv::Rect> & faces);

    // Returns array of cv::Rect objects corresponding to coordinates of faces recognized on the image
    std::vector<cv::Rect> localize_rect(cv::Mat & image);

    // Returns an array of cv::Mat of the faces recognized on the image using the array of Rect given as input
    std::vector<cv::Mat> localize(cv::Mat & image, std::vector<cv::Rect> & faces_rect);

    // Returns array of cv::Mat of faces from the image given
    std::vector<cv::Mat> localize(cv::Mat & image);
    
    int width;
    int height;
    int padding; // in percentage

    private:
};

#endif
