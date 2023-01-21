#include "cascade_conformity.hpp"
#include <vector>

const double pi = 3.14159265358979323846;

// Yassine = 0
// Romain = 1
// Other = 2
#define test 1 // To load correct haarcascade

#if test == 0
std::string path_face = "C:\\Authentification-System\\sources\\Cascade\\haarcascades\\haarcascade_frontalface_default.xml";
std::string path_left_eye = "C:\\Authentification-System\\sources\\Cascade\\haarcascades\\haarcascade_lefteye_2splits.xml";
std::string path_right_eye = "C:\\Authentification-System\\sources\\Cascade\\haarcascades\\haarcascade_righteye_2splits.xml";

#elif test == 1

std::string path_face = "/usr/local/share/opencv4/haarcascades/haarcascade_frontalface_default.xml";
std::string path_eye = "/usr/local/share/opencv4/haarcascades/haarcascade_eye.xml";

#endif


Cascade_conformity::Cascade_conformity()
{
cascade_face.load(path_face);
cascade_left_eye.load(path_left_eye);
cascade_right_eye.load(path_right_eye);
}

Cascade_conformity::~Cascade_conformity(){}

void Cascade_conformity::load_cascade_face(std::string path_f){
    cascade_face.load(path_f);
}
void Cascade_conformity::load_cascade_eyes(std::string path_left_eye, std::string path_right_eye){
    cascade_left_eye.load(path_left_eye);
    cascade_right_eye.load(path_right_eye);
}


void Cascade_conformity::isEye(cv::Mat image, std::vector<cv::Rect> &faces)
{
    std::vector <cv::Rect> lefteyes;
    std::vector <cv::Rect> righteyes;
    cv::Mat faceImage;
    for(cv::Rect &face:faces){
        lefteyes.clear(); //Reinitialize tempfaces
        righteyes.clear();
        faceImage = image(face);
        cascade_left_eye.detectMultiScale(faceImage, lefteyes, 1.06, 5, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(40, 40));
        cascade_right_eye.detectMultiScale(faceImage, righteyes, 1.06, 5, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(40, 40));
        if (lefteyes.size()==0 && righteyes.size()==0){
            faces.erase(std::remove(faces.begin(),faces.end(),face),faces.end());
        }
    }
}

void Cascade_conformity::detectMultiScale(cv::Mat image, std::vector<cv::Rect> &faces, double scaleFactor, double minNeighbors, double flags, cv::Size minSize) {
std::vector<cv::Rect> eyes;
    EyedetectMultiScale(image, eyes,  scaleFactor,  minNeighbors,  flags, minSize);
    cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(image, image);
    cascade_face.detectMultiScale(image, faces, scaleFactor, minNeighbors, flags, minSize);
    for (int i = 0; i < faces.size(); i++) {
        bool hasEyes = false;
        for (int j = 0; j < eyes.size(); j++) {
            if  (eyes[j].x >= faces[i].x && eyes[j].x + eyes[j].width <= faces[i].x + faces[i].width &&
                 eyes[j].y >= faces[i].y && eyes[j].y + eyes[j].height <= faces[i].y + faces[i].height) {
                hasEyes = true;
                break;
            }
        }
        if (!hasEyes) {
            faces.erase(faces.begin() + i);
            i--; // Decrement i to account for the deleted face
        }
    }
//    isEye(image, faces);
}

void Cascade_conformity::EyedetectMultiScale(cv::Mat image, std::vector<cv::Rect> &eyes, double scaleFactor, double minNeighbors, double flags, cv::Size minSize) {
    cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(image, image);
    std::vector<cv::Rect>templeft;
    std::vector<cv::Rect>tempright;
//	cascade_left_eye.detectMultiScale(image, templeft, scaleFactor, minNeighbors, flags, minSize);
    cascade_right_eye.detectMultiScale(image, tempright, scaleFactor, minNeighbors, flags, minSize);
    for (int i=0; i<tempright.size();i++){
//        eyes.push_back(templeft[i]);
        eyes.push_back(tempright[i]);
    }
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


