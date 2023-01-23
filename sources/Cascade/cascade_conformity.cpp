#include "cascade_conformity.hpp"
#include <vector>

const double pi = 3.14159265358979323846;

// Yassine = 0
// Romain = 1
// Other = 2
#define test 1
// To load correct haarcascade

#if test == 0
std::string path_face = "..\\sources\\Cascade\\haarcascades\\haarcascade_frontalface_default.xml";
std::string path_left_eye = "..\\sources\\Cascade\\haarcascades\\haarcascade_righteye_2splits.xml";
std::string path_right_eye = "..\\sources\\Cascade\\haarcascades\\haarcascade_eye.xml";

#elif test == 1

std::string path_face = "/Users/florencepoggi/Documents/Romain/Education/Bachelor X/Courses/Semester 3/CSE 201 - CPP/Project/Authentification-System/sources/Detect/haarcascades/haarcascade_frontalface_default.xml";
std::string path_left_eye = "/Users/florencepoggi/Documents/Romain/Education/Bachelor X/Courses/Semester 3/CSE 201 - CPP/Project/Authentification-System/sources/Detect/haarcascades/haarcascade_righteye_2splits.xml";
std::string path_right_eye = "/Users/florencepoggi/Documents/Romain/Education/Bachelor X/Courses/Semester 3/CSE 201 - CPP/Project/Authentification-System/sources/Detect/haarcascades/haarcascade_eye.xml";

#endif

Cascade_conformity::Cascade_conformity()
{
    cascade_face.load(path_face);
    cascade_left_eye.load(path_left_eye);
    cascade_right_eye.load(path_right_eye);
}

Cascade_conformity::~Cascade_conformity() {}

void Cascade_conformity::load_cascade_face(std::string path_f)
{
    cascade_face.load(path_f);
}
void Cascade_conformity::load_cascade_eyes(std::string path_left_eye, std::string path_right_eye)
{
    cascade_left_eye.load(path_left_eye);
    cascade_right_eye.load(path_right_eye);
}

void Cascade_conformity::isEye(cv::Mat image, std::vector<cv::Rect> &faces)
{
    std::vector<cv::Rect> lefteyes;
    std::vector<cv::Rect> righteyes;
    cv::Mat faceImage;
    for (cv::Rect &face : faces)
    {
        lefteyes.clear(); // Reinitialize tempfaces
        righteyes.clear();
        faceImage = image(face);
        cascade_left_eye.detectMultiScale(faceImage, lefteyes, 1.06, 5, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(40, 40));
        cascade_right_eye.detectMultiScale(faceImage, righteyes, 1.06, 5, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(40, 40));
        if (lefteyes.size() == 0 && righteyes.size() == 0)
        {
            faces.erase(std::remove(faces.begin(), faces.end(), face), faces.end());
        }
    }
}

void Cascade_conformity::detectMultiScale(cv::Mat image, std::vector<cv::Rect> &faces, double scaleFactor, double minNeighbors, double flags, cv::Size minSize)
{
    //    cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
    //    cv::equalizeHist(image, image);
    cascade_face.detectMultiScale(image, faces, scaleFactor, minNeighbors, flags, minSize);
    std::vector<cv::Rect> eyes;
    bool iseye = EyedetectMultiScale(image, eyes, scaleFactor, minNeighbors, flags, minSize);
    if (iseye == 0)
    {
        faces.clear();
    }
}
//    cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
//    cv::equalizeHist(image, image);
//    cascade_face.detectMultiScale(image, faces, scaleFactor, minNeighbors, flags, minSize);
//    for (int i = 0; i < faces.size(); i++) {
//        bool hasEyes = false;
//        for (int j = 0; j < eyes.size(); j++) {
//            if  (eyes[j].x >= faces[i].x && eyes[j].x + eyes[j].width <= faces[i].x + faces[i].width &&
//                 eyes[j].y >= faces[i].y && eyes[j].y + eyes[j].height <= faces[i].y + faces[i].height) {
//                hasEyes = true;
//                break;
//            }
//        }
//        if (!hasEyes) {
//            faces.erase(faces.begin() + i);
//            i--; // Decrement i to account for the deleted face
//        }
//    }
////    isEye(image, faces);
//}

bool Cascade_conformity::EyedetectMultiScale(cv::Mat &image, std::vector<cv::Rect> &eyes, double scaleFactor, double minNeighbors, double flags, cv::Size minSize)
{
    std::vector<cv::Rect> templeft;
    std::vector<cv::Rect> tempright;
    cascade_left_eye.detectMultiScale(image, templeft, scaleFactor, minNeighbors, flags, minSize);
    cascade_right_eye.detectMultiScale(image, tempright, scaleFactor, minNeighbors, flags, minSize);
    for (int i = 0; i < (tempright.size()); i++)
    {
        eyes.push_back(templeft[i]);
        eyes.push_back(tempright[i]);
    }
    int open_eye = 0;
    for (int i = 0; i < eyes.size(); i++)
    {
        cv::Mat eyeROI = image(eyes[i]);
        cv::cvtColor(eyeROI, eyeROI, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(eyeROI, eyeROI);

        // Threshold for the pixel intensity
        int threshold = 100;

        // Count the number of pixels above the threshold
        int count = 0;
        for (int y = 0; y < eyeROI.rows; y++)
        {
            for (int x = 0; x < eyeROI.cols; x++)
            {
                if (eyeROI.at<uchar>(y, x) > threshold)
                {
                    count++;
                }
            }
        }

        // Percentage of pixels above the threshold
        double percentage = (double)count / (eyeROI.rows * eyeROI.cols) * 100;
        if (percentage > 50)
        {
            open_eye++;
        }
    }
    if (open_eye > 0)
    {
        std::cout << "At least one eye is open" << std::endl;
        return true;
    }
    else
    {
        std::cout << "All eyes are closed" << std::endl;
        return false;
    }
}

//
// void Cascade_conformity::normalizeIntensities(cv::Mat &image)
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
