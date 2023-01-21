#include "cascade_conformity.hpp"
#include <vector>

const double pi = 3.14159265358979323846;

// Yassine = 0
// Romain = 1
// Other = 2
#define test 0 // To load correct haarcascade

#if test == 0
std::string path_face = "C:\\Authentification-System\\sources\\Cascade\\haarcascades\\haarcascade_eye.xml";
std::string path_eye = "C:\\Authentification-System\\sources\\Cascade\\haarcascades\\haarcascade_eye.xml";

#elif test == 1

std::string path_face = "/usr/local/share/opencv4/haarcascades/haarcascade_frontalface_default.xml";
std::string path_eye = "/usr/local/share/opencv4/haarcascades/haarcascade_eye.xml";

#endif


Cascade_conformity::Cascade_conformity()
{
cascade_face.load(path_face);
cascade_eyes.load(path_eye);
}

Cascade_conformity::~Cascade_conformity(){}

void Cascade_conformity::load_cascade_face(std::string path_f){
    cascade_face.load(path_f);
}
void Cascade_conformity::load_cascade_eyes(std::string path_e){
    cascade_eyes.load(path_e);
}


void Cascade_conformity::isEye(cv::Mat image, std::vector<cv::Rect> &faces)
{
    std::vector <cv::Rect> tempfaces;
    cv::Mat faceImage;
    for(cv::Rect &face:faces){
        tempfaces.clear(); //Reinitialize tempfaces
        faceImage = image(face);
        cascade_eyes.detectMultiScale(faceImage, tempfaces, 1.06, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
        if (tempfaces.size()==0){
            faces.erase(std::remove(faces.begin(),faces.end(),face),faces.end());
        }
    }
}

void Cascade_conformity::detectMultiScale(cv::Mat image, std::vector<cv::Rect> &faces, double scaleFactor, double minNeighbors, double flags, cv::Size minSize) {

    cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(image, image);
    cascade_face.detectMultiScale(image, faces, scaleFactor, minNeighbors, flags, minSize);
    isEye(image, faces);
}

void Cascade_conformity::EyedetectMultiScale(cv::Mat image, std::vector<cv::Rect> &eyes, double scaleFactor, double minNeighbors, double flags, cv::Size minSize) {
    cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(image, image);
	cascade_eyes.detectMultiScale(image, eyes, scaleFactor, minNeighbors, flags, minSize);
}

//
//void Cascade_conformity::normalizeIntensities(cv::Mat &image)
//{
//    // Convert image to grayscale
//    cv::Mat gray;
//    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
//
//    // Compute mean and standard deviation of pixel intensities
//    cv::Scalar mean, stddev;
//    cv::meanStdDev(gray, mean, stddev);
//
//    // Normalize the pixel intensities
//    image = (image - mean[0]) / stddev[0];
//}
//
//
//

