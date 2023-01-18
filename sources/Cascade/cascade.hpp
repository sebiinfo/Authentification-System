#include <opencv2/opencv.hpp>
#include <vector>
//#include "../Localization/cascadecv.hpp"

class Cascade
{

Cascade();
Cascade(int w,int h,int pad,cv::Mat img, cv::CascadeClassifier casc);
Cascade(cv::Mat img);
~Cascade();

std::vector<cv::Rect> CoordCascade();


void Tilt(); // Tilt the image so it is horizontal, it uses the eyes detection
bool Conform(); // Check if the image is in the proper format for transformation: if eyes are open, padding fits



cv::Mat Crop(cv::Rect rect); // Crops the image using coordinates given with padding

cv::Mat Resize(cv::Mat img); // Resizes the image given to the dimensions set by the class attribute



cv::Mat Transform(); // Transforms and returns the image attribute in the proper form for the algorithm


////////////////////////////////////////////
// Methods to access the class attributes //
////////////////////////////////////////////

void set_image(cv::Mat img);
void get_image(cv::Mat img);

void set_width(int w);
int get_width();

void set_height(int h);
int get_height();

void set_padding(int pad);
int get_padding();


void load_cascade(cv::CascadeClassifier cascade);
cv::CascadeClassifier get_cascade();

private:
    cv::Mat image; // The image we work on in the class
    cv::CascadeClassifier cascade; // The cascade we use for detection

    int width; // Width of the size of the image we want to trasnform
    int height; // Height of the size of the image we want to trasnform
    int padding; // Padding we will add when transforming

};
