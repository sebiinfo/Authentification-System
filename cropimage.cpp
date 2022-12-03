#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;


void inplaceCrop (Mat image ,int w1,int w2,int h1,int h2){
    image = image(Range(w1,w2), Range(h1,h2));
    };

Mat Crop(Mat image ,int w1,int w2,int h1,int h2){
    return image(Range(w1,w2), Range(h1,h2));
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


void showFrame(Mat frame,string name="Frame"){
    for(;;){
        imshow("webcam",frame);

        if(waitKey(30)>=0){break;}
    }
}

void runwebcam(){
    VideoCapture cap(0);
    if (!cap.isOpened()){
        return;
    };
    for(;;){
        Mat frame;
        cap >> frame;
        imshow("webcam",frame);

        if(waitKey(30)>=0){break;}
    }
}

vector<Rect> CoordFace(Mat frame,string path,double scale,Size size)
{

    CascadeClassifier faceCascade;
    faceCascade.load(path);


    Mat grayscale;
    cvtColor(frame,grayscale,COLOR_BGR2GRAY);
    resize(grayscale,grayscale, Size(grayscale.rows / scale, grayscale.cols / scale ) );


    vector<Rect> faces;
    faceCascade.detectMultiScale(grayscale,faces,1.1,3,0,size);

    return faces;
};


void detectface(Mat frame,string path,double scale =1.0,Size size=Size(50,50),Scalar drawColor = Scalar(255,0,0)){

    CascadeClassifier faceCascade;
    faceCascade.load(path);

    Mat grayscale;
    cvtColor(frame,grayscale,COLOR_BGR2GRAY);
//    equalizeHist( grayscale, grayscale );

    resize(grayscale,grayscale, Size(grayscale.rows / scale, grayscale.cols / scale ) );

    vector<Rect> faces;
    faceCascade.detectMultiScale(grayscale,faces,1.1,3,0,Size(50,50));


    for(Rect area : faces)
    {
       Point p1 = Point(cvRound(area.x * scale),cvRound(area.y * scale));
       Point p2 = Point(cvRound((area.x + area.width-1) * scale),cvRound((area.y+area.height -1)* scale));
       rectangle(frame,p1,p2,drawColor);
    }

     showFrame(frame);
}

void runCascadeFace(string path)
{
    CascadeClassifier faceCascade;
    faceCascade.load(path);

    double scale = 1.0;
    Size size = Size(50,50);

    VideoCapture cap(0);
    if (!cap.isOpened()){
        return;
    };

    Scalar drawColor = Scalar(255,0,0);

    for(;;){
        Mat frame;
        cap >> frame;


        vector<Rect> faces = CoordFace(frame,path,scale,size);


        for(Rect area : faces)
        {
           Point p1 = Point(cvRound(area.x * scale),cvRound(area.y * scale));
           Point p2 = Point(cvRound((area.x + area.width-1) * scale),cvRound((area.y+area.height -1)* scale));
           rectangle(frame,p1,p2,drawColor);
        }

        imshow("webcam",frame);

        if(waitKey(30)>=0){break;}
    }

}

//int main(int argc, char **argv)
//{
//  return 0;
//}

