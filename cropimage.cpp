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

void draw(Mat& img, vector<Rect> faces,double scale,int margin)
{

    for (size_t i = 0; i < faces.size(); i++)
    {
        Rect r = faces[i];
        Mat smallImgROI;
        Scalar color = Scalar(255, 0, 0); // Color for Drawing tool
        rectangle(img, Point(cvRound(r.x*scale-margin), cvRound(r.y*scale-margin)),
                    Point(cvRound((r.x + r.width-1)*scale+margin),
                    cvRound((r.y + r.height-1)*scale+margin)), color, 3, 8, 0);
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
                            2, 0|CASCADE_SCALE_IMAGE, Size(30, 30)),Size(50,50);
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
            draw(frame1,faces,scale,50);
            char c = (char)waitKey(10);

            // Press q to exit from window
            if( c == 27 || c == 'q' || c == 'Q' )
                break;

            imshow("Cam",frame1);
        }
    }
    else {cout<<"Could not Open Camera";}

}

vector<Mat> cropWithRect(Mat frame, vector<Rect> faces)
{
    vector<Mat> frameVect;
    int x,w,y,h;
    Mat img;

    for (size_t i = 0; i < faces.size(); i++)
    {
        Rect r = faces[i];
        x = r.x;
        w = r.width;
        y = r.y;
        h = r.height;

        img = frame.clone();
        cropOne(img,x,x+w,y,y+h);

        frameVect.push_back(img.clone());

    };
    return frameVect;
}

vector<Mat> crop(Mat frame,string path)
{
    double scale = 1;
    CascadeClassifier cascade;
    cascade.load(path);

    vector<Rect> faces = detect(frame,cascade,scale);

    return cropWithRect(frame,faces);

}


void showCrop(Mat frame,string path)
{

    vector<Mat> v = crop(frame,path);
    int n = v.size();

    for(int i=0; i<n ;i++)
    {
        showFrame(v[i]);
    }
}

void test(){
    cout<<"Sex";
}

//Please do not use using namespace. I know it is annoying to not but it will be beneficial in the long run. Thank you :) 
