//#include <opencv2/opencv.hpp>
//#include <opencv2/objdetect/objdetect.hpp>
//#include "detect.hpp"
//#include "C:\Authentification-System\sources\Cascade\cascade_detect_cv.hpp"
//#include <vector>
//
//// Yassine = 0
//// Romain = 1
//// Other = 2
//#define test 0 // To load correct haarcascade
//
//#if test == 0
////std::string path_face = "C:\\Authentification-System\\sources\\Detect\\haarcascades\\haarcascade_eye.xml";
////std::string path_eye = "C:\\Authentification-System\\sources\\Detect\\haarcascades\\haarcascade_eye.xml";
//
//#elif test == 1
//
//std::string path_face = "/Users/florencepoggi/Documents/Romain/Education/Bachelor X/Courses/Semester 3/CSE 201 - CPP/Project/Authentification-System/sources/Detect/haarcascades/haarcascade_frontalface_default.xml";
//std::string path_eye = "/Users/florencepoggi/Documents/Romain/Education/Bachelor X/Courses/Semester 3/CSE 201 - CPP/Project/Authentification-System/sources/Detect/haarcascades/haarcascade_eye.xml";
//
//#endif
//
//const double pi = 3.14159265358979323846;
//
//
//void normalizeIntensities(cv::Mat &image)
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
////bool isEyeOpen(cv::Mat frame)
////{
////    // Load the Haar cascade classifier for eye detection
////    cascade_detect_cv cascade= cascade_detect_cv();
////
////
////    // Detect eyes in the image using the Haar cascade classifier
////    std::vector<cv::Rect> eyes;
////    eyeCascade.detectMultiScale(frame, eyes, 1.06, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
////    return eyes.size() > 0;
////}
//
//bool isFace(cv::Mat image)
//{
//    std::vector<cv::Rect> faces = detectFaces(image);
//    return faces.size() > 0;
//}
//
//bool isEye(cv::Mat image)
//{
//    std::vector<cv::Rect> eyes = detectEyes(image);
//    return eyes.size() > 0;
//}
//
//std::vector<cv::Rect> detectFaces(cv::Mat image)
//{
//    cv::CascadeClassifier faceCascade;
//    if (!faceCascade.load(path_face))
//    {
//        std::cout << "Failed to load the face cascade at directory:" << path_face << std::endl;
//    }
//
//    std::vector<cv::Rect> faces;
//    faceCascade.detectMultiScale(image, faces, 1.06, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
//
//    return faces;
//}
//
//std::vector<cv::Rect> detectEyes(cv::Mat image)
//{
//    cv::CascadeClassifier faceCascade;
//    if (!faceCascade.load(path_eye))
//    {
//        std::cout << "Failed to load the face cascade:" << path_face << std::endl;
//    }
//
//    std::vector<cv::Rect> faces;
//    faceCascade.detectMultiScale(image, faces, 1.06, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
//
//    return faces;
//}
//
//bool conform(cv::Mat image)
//{
//    if (!isFace(image))
//    {
//        //        std::cout << "No face was found";
//        return false;
//    }
//    if (isEyeOpen(image))
//    {
//        //        std::cout << "Face and eyes are open";
//        return true;
//    }
//    //    std::cout << "Face was found but eyes were closed";
//    return false;
//}
//
//std::vector<cv::Mat> conformArray(std::vector<cv::Mat> faces)
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
//
////cv::Mat rotate_face(cv::Mat &image)
//double rotate_face(cv::Mat &image)
//{
//
//    // Load cascades
//    cv::CascadeClassifier face_cascade;
//    if (!face_cascade.load(path_face))
//    {
//        std::cout << "Failed to load the face cascade: " << path_face << std::endl;
//    }
//    cv::CascadeClassifier eye_cascade;
//    if (!eye_cascade.load(path_eye))
//    {
//        std::cout << "Failed to load the eye cascade: " << path_eye << std::endl;
//    }
//    // Convert to grayscale
//    cv::Mat gray;
//    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
//    std::vector<cv::Rect> faces= detectFaces(gray);
//    int x, y, w, h;
//    for (int i = 0; i < faces.size(); i++)
//    {
//        x = faces[i].x;
//        y = faces[i].y;
//        w = faces[i].width;
//        h = faces[i].height;
//        cv::rectangle(image, cv::Point(x, y), cv::Point(x + w, y + h), cv::Scalar(0, 255, 0), 2);
//        cv::circle(image, cv::Point(x + int(w * 0.5), y + int(h * 0.5)), 4, cv::Scalar(0, 255, 0), -1);
//    }
//    std::vector<cv::Rect> eyes;
//    eye_cascade.detectMultiScale(gray(cv::Rect(x, y, w, h)), eyes, 1.1, 4);
//    int index = 0;
//    cv::Rect eye_1(0, 0, 0, 0);
//    cv::Rect eye_2(0, 0, 0, 0);
//    for (int i = 0; i < eyes.size(); i++)
//    {
//        if (index == 0)
//        {
//            eye_1 = eyes[i];
//        }
//        else if (index == 1)
//        {
//            eye_2 = eyes[i];
//        }
//        index++;
//    }
//    if (eye_1.x != 0 && eye_2.x != 0)
//    {
//        cv::Rect left_eye;
//        cv::Rect right_eye;
//        if (eye_1.x < eye_2.x)
//        {
//            left_eye = eye_1;
//            right_eye = eye_2;
//        }
//        else
//        {
//            left_eye = eye_2;
//            right_eye = eye_1;
//        }
//        cv::Point left_eye_center = cv::Point(left_eye.x + (left_eye.width / 2),
//                                              left_eye.y + (left_eye.height / 2));
//        cv::Point right_eye_center = cv::Point(right_eye.x + (right_eye.width / 2),
//                                               right_eye.y + (right_eye.height / 2));
//        double left_eye_x = left_eye_center.x;
//        double left_eye_y = left_eye_center.y;
//        double right_eye_x = right_eye_center.x;
//        double right_eye_y = right_eye_center.y;
//        double delta_x, delta_y;
//        delta_x = right_eye_x - left_eye_x;
//        delta_y = right_eye_y - left_eye_y;
//        double angle;
//        if (delta_x==0 || delta_y==0){
//            angle=0;
//        }
//        else {
//            double angle_rad = std::atan(delta_y / delta_x);
//             angle = (angle_rad * 180) / pi;
//        }
//        return angle;
////        if (angle > 10){ // If a right tilt is detected
////            // Rotate face left
////            return rotate_face_aux(image, angle);
////        }
////        else if (angle < -10){ // If a left tilt is detected
////            // Rotate face right
////            return rotate_face_aux(image, angle);
////        }
////        else
////        {
////            return image;
////        }
//    }
//    return 0;
//}
//
//cv::Mat rotate_face_aux(cv::Mat &image, double angle)
//{
//    //    cv::Size s= image.size();
//    //    double height =s.height;
//    //    double width = s.width;
//    int height, width;
//
//    height = image.rows;
//    width = image.cols;
//
//    cv::Point2f image_center = cv::Point(height / 2, width / 2);
//    cv::Mat rotation_mat = cv::getRotationMatrix2D(image_center, angle, 1);
//
//    double abs_cos = abs(cos(angle));
//    double abs_sin = abs(sin(angle));
//    int bound_w = height * abs_sin + width * abs_cos;
//    int bound_h = height * abs_cos + width * abs_sin;
//
//    rotation_mat.at<double>(0, 2) += bound_w / 2 - image_center.x;
//    rotation_mat.at<double>(1, 2) += bound_h / 2 - image_center.y;
//
//    cv::Mat rotated_mat;
//    cv::warpAffine(image, rotated_mat, rotation_mat, cv::Size(bound_w, bound_h));
//
//    return rotated_mat;
//}