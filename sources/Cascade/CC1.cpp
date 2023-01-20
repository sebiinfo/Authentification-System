#include "cascade_conformity.hpp"
const double pi = 3.14159265358979323846;

// Yassine = 0
// Romain = 1
// Other = 2
#define test 0 // To load correct haarcascade

#if test == 0
std::string path_face = "C:\\Authentification-System\\sources\\Detect\\haarcascades\\haarcascade_eye.xml";
std::string path_eye = "C:\\Authentification-System\\sources\\Detect\\haarcascades\\haarcascade_eye.xml";

#elif test == 1

std::string path_face = "/Users/florencepoggi/Documents/Romain/Education/Bachelor X/Courses/Semester 3/CSE 201 - CPP/Project/Authentification-System/sources/Detect/haarcascades/haarcascade_frontalface_default.xml";
std::string path_eye = "/Users/florencepoggi/Documents/Romain/Education/Bachelor X/Courses/Semester 3/CSE 201 - CPP/Project/Authentification-System/sources/Detect/haarcascades/haarcascade_eye.xml";
#endif


Cascade_conformity::Cascade_conformity() {
    //Empty vector
    faces=std::vector<cv::Mat>();
    cascade_face.load(path_face);
    cascade_eyes.load(path_eye);
}

Cascade_conformity::Cascade_conformity(std::vector<cv::Mat> &input_faces) {
    //Empty vector
    faces=input_faces;
    cascade_face.load(path_face);
    cascade_eyes.load(path_eye);
}
Cascade_conformity::~Cascade_conformity(){}

void Cascade_conformity::detectMultiScale(cv::Mat image, std::vector<cv::Mat> &faces, double scaleFactor, double minNeighbors, double flags, cv::Size minSize) {

    cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(image, image);
    std::vector<cv::Mat> tempfaces;
    cascade_face.detectMultiScale(image,tempfaces, scaleFactor, minNeighbors, flags, minSize );
    for (int i=0; i<tempfaces.size(); i++){
        if (conform(tempfaces[i])){
            faces.push_back(faces[i]);
        }
    }

}
void Cascade_conformity::append_face(cv::Mat image){
    faces.push_back(image);
}

cv::Mat Cascade_conformity::get_face(int i) {
    return faces[i];
}

bool Cascade_conformity::isEyeOpen(cv::Mat frame)
{
    // Load the Haar cascade classifier for eye detection
    cv::CascadeClassifier eyeCascade;
    eyeCascade.load(path_face);

    // Detect eyes in the image using the Haar cascade classifier
    std::vector<cv::Rect> eyes;
    eyeCascade.detectMultiScale(frame, eyes, 1.06, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
    return eyes.size() > 0;
}

bool Cascade_conformity::isFace(cv::Mat image)
{
    std::vector<cv::Mat> faces = detectFaces(image);
    return faces.size() > 0;
}

bool Cascade_conformity::isEye(cv::Mat image)
{
    std::vector<cv::Mat> eyes = detectEyes(image);
    return eyes.size() > 0;
}

std::vector<cv::Mat> Cascade_conformity::detectFaces(cv::Mat image)
{
    cv::CascadeClassifier faceCascade;
    if (!faceCascade.load(path_face))
    {
        std::cout << "Failed to load the face cascade at directory:" << path_face << std::endl;
    }

    std::vector<cv::Mat> faces;
    faceCascade.detectMultiScale(image, faces, 1.06, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

    return faces;
}

std::vector<cv::Mat> Cascade_conformity::detectEyes(cv::Mat image)
{
    cv::CascadeClassifier faceCascade;
    if (!faceCascade.load(path_eye))
    {
        std::cout << "Failed to load the face cascade:" << path_face << std::endl;
    }

    std::vector<cv::Mat> faces;
    faceCascade.detectMultiScale(image, faces, 1.06, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

    return faces;
}

bool Cascade_conformity::conform(cv::Mat image, bool smartcascade/*=true*/) {
    // if smartcascade==true, we only take the images that are conform into the conformity vector faces.

    if (smartcascade == true) {
        if (isFace(image)) {
            if (isEye(image)) {
                double angle = get_angle_from_eyes(image);
                rotate_face(image, angle);
                return true;
            } else {
                std::cout << "Face was found but eyes were closed";
                return false;
            }
        } else {
            std::cout << "No face was found";
            return false;
        }
    }
}


std::vector<cv::Mat> Cascade_conformity::conformArray(std::vector<cv::Mat> faces)
{
    std::vector<cv::Mat> conformArray;
    for (int i = 0; i < faces.size(); i++)
    {
        if (conform(faces[i]))
        {
            conformArray.push_back(faces[i]);
        }
    }
    return conformArray;
}

//cv::Mat rotate_face(cv::Mat &image)


cv::Mat Cascade_conformity::convert_rect_to_mat(cv::Rect &rect) {
    cv::Mat rec_to_mat;
    cv::Mat rec_to_mat= rec_to_mat(rect);

}
void Cascade_conformity::normalizeIntensities(cv::Mat &image)
{
    // Convert image to grayscale
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    // Compute mean and standard deviation of pixel intensities
    cv::Scalar mean, stddev;
    cv::meanStdDev(gray, mean, stddev);

    // Normalize the pixel intensities
    image = (image - mean[0]) / stddev[0];
}





