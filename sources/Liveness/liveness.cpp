#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char* argv[])
{

    // This code takes the camera capture and tells weather the input is
    //  a live input of a person or not by computing th optimal flow
    // however this has been written separately as a main and the next steps
    // are to integrate it with the rest of the project and particularly
    // understand where does this fit in the general architecture of the project


    // Read the video from the default camera
    cv::VideoCapture cap(0);

    // Check if the camera is opened
    if(!cap.isOpened())
    {
        std::cout << "Error opening video stream or file" << std::endl;
        return -1;
    }

    //  width and height of the frames
    int frame_width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int frame_height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));

    // VideoWriter object for the output video
    cv::VideoWriter video("out.avi", cv::VideoWriter::fourcc('M','J','P','G'), 10, cv::Size(frame_width,frame_height));

    // Check VideoWriter object
    if(!video.isOpened())
    {
        std::cout << "Error opening video writer" << std::endl;
        return -1;
    }

    // window to display the frames
    cv::namedWindow("Frame", cv::WINDOW_NORMAL);

    // face detector haarcascades
    cv::CascadeClassifier face_detector;
    face_detector.load("haarcascade_frontalface_default.xml");

    // initialization
    cv::Mat frame, gray, prev_gray, flow, cflow;
    std::vector<cv::Point2f> points[2];
    std::vector<cv::Rect> faces;
    bool is_face_present = false;



    // release the video capture and writer objects
    cap.release();
    video.release();

    cv::destroyAllWindows();

    return 0;
}
