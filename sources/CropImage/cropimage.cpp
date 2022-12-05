#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include <string>
#include "cropimage.hpp"

using namespace cv;
using namespace std;


void cropOne (Mat& image ,int x1,int x2,int y1,int y2){
    // image(Range(start_row, end_row), Range(start_col, end_col))
    image = image(Range(y1,y2), Range(x1,x2));
    };

Mat getFrame(){
    VideoCapture cap(0);
    if (!cap.isOpened()){
        return Mat();
    };
    Mat frame;
    cap >> frame;
    return frame;
}


void showFrame(Mat frame){
    while(true)
    {
        char c = (char)waitKey(10);

        // Press q to exit from window
        if( c == 27 || c == 'q' || c == 'Q' )
            break;

        imshow("Cam",frame);
    }
}

void runwebcam(){
    VideoCapture capture;
    Mat frame;

    if (capture.isOpened())
    {
        while(true)
        {
            capture >> frame;
            if(frame.empty())
                break;

            char c = (char)waitKey(10);

            // Press q to exit from window
            if( c == 27 || c == 'q' || c == 'Q' )
                break;

            imshow("Cam",frame);
        }
    }
}

void draw(Mat& img, vector<Rect> faces,double scale)
{

    int c = 50;
    for (size_t i = 0; i < faces.size(); i++)
    {
        Rect r = faces[i];
        Mat smallImgROI;
        Scalar color = Scalar(255, 0, 0); // Color for Drawing tool
        rectangle(img, Point(cvRound(r.x*scale-c), cvRound(r.y*scale-c)),
                    Point(cvRound((r.x + r.width-1)*scale+c),
                    cvRound((r.y + r.height-1)*scale+c)), color, 3, 8, 0);
    }
}


vector<Rect> detect(Mat& img, CascadeClassifier& cascade, double scale){
    vector<Rect> faces;
    Mat gray, smallImg;

    cvtColor(img, gray, COLOR_BGR2GRAY); // Convert to Gray Scale
    double fx = 1 / scale;

    // Resize the Grayscale Image
    resize(gray, smallImg, Size(), fx, fx, INTER_LINEAR);
    equalizeHist(smallImg, smallImg);

    // Detect faces of different sizes using cascade classifier
    cascade.detectMultiScale(smallImg, faces, 1.1,
                            2, 0|CASCADE_SCALE_IMAGE, Size(30, 30));
    return faces;
}

void runCascadeFace(string path){
    VideoCapture capture;
    Mat frame, image;

    CascadeClassifier cascade;
    double scale=5;

    cascade.load(path);

    capture.open(0);
    if (capture.isOpened())
    {
        while(true)
        {
            capture >> frame;
            if(frame.empty())
                break;
            Mat frame1 = frame.clone();
            vector<Rect> faces = detect(frame1,cascade,scale);
            draw(frame1,faces,scale);
            char c = (char)waitKey(10);

            // Press q to exit from window
            if( c == 27 || c == 'q' || c == 'Q' )
                break;

            imshow("Cam",frame1);
        }
    }
    else {cout<<"Could not Open Camera";}

}

// DOES NOT WORK YET
vector<Mat> cropWithRect(Mat frame, vector<Rect> faces)
{
    vector<Mat> frameVect;

    for (size_t i = 0; i < faces.size(); i++)
    {
        Rect r = faces[i];

//        Mat smallImgROI = frame.clone();
        cout << 2;
        cropOne(frame,r.x,r.x+r.width,r.y,r.y+r.height);
        cout << 3;

        frameVect.push_back(frame.clone());
//        frame.copyTo(frameList.back());
        cout << 4;

    };
    return frameVect;
}

// SHOULD WORK WHEN cropWithRect FIXED
vector<Mat> crop(Mat frame,string path)
{
    double scale = 1;
    CascadeClassifier cascade;
    cascade.load(path);

    vector<Rect> faces = detect(frame,cascade,scale);

    return cropWithRect(frame,faces);

//    return vector<Mat>();
}
