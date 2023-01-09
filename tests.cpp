#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include <string>
//#include "sources/Cropimage/cropimage.hpp"

cv::Mat getFrame(){
    cv::VideoCapture cap(0);
    if (!cap.isOpened()){
        return cv::Mat();
    };
    cv::Mat frame;
    cap >> frame;
    return frame;
}

void showFrame(cv::Mat frame){
    while(true)
    {
        char c = (char)cv::waitKey(10);

        // Press q to exit from window
        if( c == 27 || c == 'q' || c == 'Q' )
            break;

        imshow("Cam",frame);
    }
}

void runwebcam(){
    cv::VideoCapture capture;
    cv::Mat frame;

    if (capture.isOpened())
    {
        while(true)
        {
            capture >> frame;
            if(frame.empty())
                break;

            char c = (char)cv::waitKey(10);

            // Press q to exit from window
            if( c == 27 || c == 'q' || c == 'Q' )
                break;

            imshow("Cam",frame);
        }
    }else
    {
        std::cout << "Could not open camera";
    };
}

//void runCascadeFace(std::string path){
//    cv::VideoCapture capture;
//    cv::Mat frame, image;

//    cv::CascadeClassifier cascade;
//    double scale=5;

//    cascade.load(path);

//    capture.open(0);
//    if (capture.isOpened())
//    {
//        while(true)
//        {
//            capture >> frame;
//            if(frame.empty())
//                break;
//            cv::Mat frame1 = frame.clone();
//            std::vector<cv::Rect> faces = detect(frame1,cascade,scale);
//            draw(frame1,faces,scale,50);
//            char c = (char)cv::waitKey(10);

//            // Press q to exit from window
//            if( c == 27 || c == 'q' || c == 'Q' )
//                break;

//            imshow("Cam",frame1);
//        }
//    }
//    else {std::cout<<"Could not Open Camera";}

//}

void test(){
    getFrame();
}
