#include <cassert>
#include "cascade_Base.hpp"

#define test 0

#if test==0

//std::string path_face = "/usr/local/share/opencv4/haarcascades/haarcascade_frontalface_default.xml";
//std::string path_eye = "/usr/local/share/opencv4/haarcascades/haarcascade_eye.xml";

#endif



cascade_Base::cascade_Base(){}
cascade_Base::~ cascade_Base(){}

void cascade_Base::detectMultiScale(cv::Mat image, std::vector <cv::Rect> &faces, double scaleFactor, double minNeighbors, double flags, cv::Size minSize){

    assert(false);

}

// void cascade_Base::detectMultiScale(cv::Mat image, std::vector<cv::Rect> &faces)
// {
//     assert(false);
// }


void cascade_Base::Special_Transform(){
    assert(false);
}
