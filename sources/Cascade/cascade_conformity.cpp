#include "cascade_conformity.hpp"
const double pi = 3.14159265358979323846;

// Yassine = 0
// Romain = 1
// Other = 2
#define test 0 // To load correct haarcascade

#if test == 0
std::string path_face = "C:\\Authentification-System\\sources\\Cascade\\haarcascades\\haarcascade_eye.xml";
std::string path_eye = "C:\\Authentification-System\\sources\\Cascade\\haarcascades\\haarcascade_eye.xml";

#elif test == 1

std::string path_face = "/Users/florencepoggi/Documents/Romain/Education/Bachelor X/Courses/Semester 3/CSE 201 - CPP/Project/Authentification-System/sources/Detect/haarcascades/haarcascade_frontalface_default.xml";
std::string path_eye = "/Users/florencepoggi/Documents/Romain/Education/Bachelor X/Courses/Semester 3/CSE 201 - CPP/Project/Authentification-System/sources/Detect/haarcascades/haarcascade_eye.xml";
#endif


Cascade_conformity::Cascade_conformity() {
    //Empty vector
    vect_faces=std::vector<cv::Rect>();
    cascade_face.load(path_face);
    cascade_eyes.load(path_eye);
}

Cascade_conformity::Cascade_conformity(std::vector<cv::Rect> &input_faces) {

    vect_faces=input_faces;
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

std::vector<cv::Rect> Cascade_conformity::detectFaces(cv::Mat &image)
{
    std::vector <cv::Rect> tempfaces;
    cascade_face.detectMultiScale(image, tempfaces, 1.06, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
    vect_faces=tempfaces;
    return tempfaces;
}

std::vector<cv::Rect> Cascade_conformity::detectEyes(cv::Mat image)
{
    std::vector<cv::Rect> tempfaces;
    cascade_eyes.detectMultiScale(image, tempfaces, 1.06, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
    vect_faces=tempfaces;
    return tempfaces;
}

bool Cascade_conformity::isFace(cv::Mat image)
{
    vect_faces = detectFaces(image);
    return vect_faces.size() > 0;
}
bool Cascade_conformity::isEye(cv::Mat image)
{
    vect_faces = detectEyes(image);
    return vect_faces.size() > 0;
}
double Cascade_conformity::get_angle_from_eyes(cv::Mat &image) {

    // Load cascades
    cv::CascadeClassifier face_cascade;
    if (!face_cascade.load(path_face))
    {
        std::cout << "Failed to load the face cascade: " << path_face << std::endl;
    }
    cv::CascadeClassifier eye_cascade;
    if (!eye_cascade.load(path_eye))
    {
        std::cout << "Failed to load the eye cascade: " << path_eye << std::endl;
    }
    // Convert to grayscale
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    std::vector<cv::Rect> faces= detectFaces(gray);
    int x, y, w, h;
    for (int i = 0; i < faces.size(); i++)
    {
        x = faces[i].x;
        y = faces[i].y;
        w = faces[i].width;
        h = faces[i].height;
        cv::rectangle(image, cv::Point(x, y), cv::Point(x + w, y + h), cv::Scalar(0, 255, 0), 2);
        cv::circle(image, cv::Point(x + int(w * 0.5), y + int(h * 0.5)), 4, cv::Scalar(0, 255, 0), -1);
    }
    std::vector<cv::Rect> eyes;
    eye_cascade.detectMultiScale(gray(cv::Rect(x, y, w, h)), eyes, 1.1, 4);
    int index = 0;
    cv::Rect eye_1(0, 0, 0, 0);
    cv::Rect eye_2(0, 0, 0, 0);
    for (int i = 0; i < eyes.size(); i++)
    {
        if (index == 0)
        {
            eye_1 = eyes[i];
        }
        else if (index == 1)
        {
            eye_2 = eyes[i];
        }
        index++;
    }
    if (eye_1.x != 0 && eye_2.x != 0)
    {
        cv::Rect left_eye;
        cv::Rect right_eye;
        if (eye_1.x < eye_2.x)
        {
            left_eye = eye_1;
            right_eye = eye_2;
        }
        else
        {
            left_eye = eye_2;
            right_eye = eye_1;
        }
        cv::Point left_eye_center = cv::Point(left_eye.x + (left_eye.width / 2),
                                              left_eye.y + (left_eye.height / 2));
        cv::Point right_eye_center = cv::Point(right_eye.x + (right_eye.width / 2),
                                               right_eye.y + (right_eye.height / 2));
        double left_eye_x = left_eye_center.x;
        double left_eye_y = left_eye_center.y;
        double right_eye_x = right_eye_center.x;
        double right_eye_y = right_eye_center.y;
        double delta_x, delta_y;
        delta_x = right_eye_x - left_eye_x;
        delta_y = right_eye_y - left_eye_y;
        double angle;
        if (delta_x==0 || delta_y==0){
            angle=0;
        }
        else {
            double angle_rad = std::atan(delta_y / delta_x);
            angle = (angle_rad * 180) / pi;
        }
        return angle;
    }
    return 0;
}



void Cascade_conformity::detectMultiScale(cv::Mat image, std::vector<cv::Rect> &faces, double scaleFactor, double minNeighbors, double flags, cv::Size minSize) {

    cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(image, image);
    std::vector<cv::Rect> tempfaces;
    cascade_face.detectMultiScale(image,tempfaces, scaleFactor, minNeighbors, flags, minSize );
//    for (int i=0; i<tempfaces.size(); i++){
//        if (conform(tempfaces[i])){
//         faces.push_back(faces[i]);
//        }
//    }

}


cv::Rect Cascade_conformity::get_face(int i) {
    return vect_faces[i];
}
cv::Mat Cascade_conformity::convert_rect_to_mat(cv::Rect &rect) {
    cv::Mat rec_to_mat;
    rec_to_mat= rec_to_mat(rect);
	return cv::Mat();
}

//bool Cascade_conformity::isEyeOpen(cv::Mat frame)
//{
//    // Load the Haar cascade classifier for eye detection
//    cv::CascadeClassifier eyeCascade;
//    eyeCascade.load(path_face);
//
//    // Detect eyes in the image using the Haar cascade classifier
//    std::vector<cv::Rect> eyes;
//    eyeCascade.detectMultiScale(frame, eyes, 1.06, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
//    return eyes.size() > 0;
//}
//
//
//bool Cascade_conformity::conform(cv::Mat image, bool smartcascade/*=true*/) {
//    // if smartcascade==true, we only take the images that are conform into the conformity vector faces.
//
//    if (smartcascade == true) {
//        if (isFace(image)) {
//            if (isEye(image)) {
//                double angle = get_angle_from_eyes(image);
//                rotate_face(image, angle);
//                return true;
//            } else {
//                std::cout << "Face was found but eyes were closed";
//                return false;
//            }
//        } else {
//            std::cout << "No face was found";
//            return false;
//        }
//    }
//}

//
//std::vector<cv::Mat> Cascade_conformity::conformArray(std::vector<cv::Mat> faces)
//{
//    std::vector<cv::Mat> conformArray;
//    for (int i = 0; i < faces.size(); i++)
//    {
//        if (conform(faces[i]))
//        {
//            conformArray.push_back(faces[i]);
//        }
//    }
//    return conformArray;
//}

//cv::Mat rotate_face(cv::Mat &image)


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


