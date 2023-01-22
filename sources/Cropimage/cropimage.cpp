#include <vector>
#include <iostream>
#include <string>
#include "cropimage.hpp"


void crop (cv::Mat& image ,int x1,int x2,int y1,int y2)
{
    //  y2
    //
    //  x1:y1      x2
    image = image(cv::Range(y1,y2), cv::Range(x1,x2));
}

std::vector<cv::Mat> cropArray (cv::Mat image, std::vector<cv::Rect> faces_rect)
{
    std::vector<cv::Mat> face_array;
    int x,w,y,h;
    cv::Mat face;
    cv::Rect r;

    for (size_t i = 0; i < faces_rect.size(); i++)
    {
        r = faces_rect[i];
//        std::cout << r.size() << std::endl;
        x = r.x;
        w = r.width;
        y = r.y;
        h = r.height;

        face = image.clone();
        crop(face,x,x+w,y,y+h);

        face_array.push_back(face.clone());

    };
    return face_array;
}

bool is_pad (cv::Mat image, cv::Rect face,int pad){
    int padx, pady,boundx, boundy;
    int w,h;
    boundx = image.cols;
    boundy = image.dims;

    w = face.width;
    h = face.height;
    padx = round ( pad * w / 100);
    pady = round ( pad * h / 100);

    if(face.x-padx < 0){return false;} // Left side

    if(face.x+w+padx > boundx){return false;} // Right side

    if(face.y-pady < 0){return false;} // Bottom side

    if(face.y+h+pady > boundy){return false;} // Top side

    return true;
}

void cropPad(cv::Mat& image,cv::Rect face,int pad)
{
    if (!is_pad(image,face,pad))
    {
        return;
    }

    int padx,pady,w,h,x,y;
    w = face.width;
    h = face.height;
    x = face.x;
    y = face.y;

    padx = round(w * pad / 100);
    pady = round(h * pad / 100);

    crop(image,x-padx,x+w+padx,y-pady,y+h+pady);

}

std::vector<cv::Mat> cropArrayPad(cv::Mat &image, std::vector<cv::Rect> faces_rect,int pad)
{
    std::vector<cv::Mat> face_array;
    int x,w,y,h;
    cv::Mat face;
    cv::Rect r;

    for (size_t i = 0; i < faces_rect.size(); i++)
    {
        r = faces_rect[i];

        face = image.clone();
        cropPad(face,r,pad);

        face_array.push_back(face.clone());

    };
    return face_array;
}





//std::vector<cv::Rect> detect(cv::Mat& img, cv::CascadeClassifier& cascade, double scale){
//    std::vector<cv::Rect> faces;
//    cv::Mat gray, smallImg;

//    cvtColor(img, gray, cv::COLOR_BGR2GRAY); // Convert to Gray Scale
//    double fx = 1 / scale;

//    // Resize the Grayscale Image
//    resize(gray, smallImg, cv::Size(), fx, fx, cv::INTER_LINEAR);
//    equalizeHist(smallImg, smallImg);

//    // Detect faces of different sizes using cascade classifier
//    cascade.detectMultiScale(smallImg, faces, 1.1,
//                            2, 0|cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30)),cv::Size(50,50);
//    return faces;
//}


//std::vector<cv::Mat> cropWithRect(cv::Mat frame, std::vector<cv::Rect> faces)
//{
//    std::vector<cv::Mat> frameVect;
//    int x,w,y,h;
//    cv::Mat img;

//    for (size_t i = 0; i < faces.size(); i++)
//    {
//        cv::Rect r = faces[i];
//        x = r.x;
//        w = r.width;
//        y = r.y;
//        h = r.height;

//        img = frame.clone();
//        cropOne(img,x,x+w,y,y+h);

//        frameVect.push_back(img.clone());

//    };
//    return frameVect;
//}

//std::vector<cv::Mat> crop(cv::Mat frame,std::string path)
//{
//    double scale = 1;
//    cv::CascadeClassifier cascade;
//    cascade.load(path);

//    std::vector<cv::Rect> faces = detect(frame,cascade,scale);

//    return cropWithRect(frame,faces);

//}


//void showCrop(cv::Mat frame,std::string path)
//{

//    std::vector<cv::Mat> crops = crop(frame,path);

//    for(int i=0; i<crops.size() ;i++)
//    {
//        while(true)
//            {
//                char c = (char)cv::waitKey(10);

//                // Press q to exit from window
//                if( c == 27 || c == 'q' || c == 'Q' )
//                    break;

//                imshow("Cam",crops[i]);
//            }
////        showFrame(crops[i]);
//    }
//}


/////////////////

//cv::Mat getFrame(){
//   cv::VideoCapture cap(0);
//   if (!cap.isOpened()){
//       return cv::Mat();
//   };
//   cv::Mat frame;
//   cap >> frame;
//   return frame;
//}

//void showFrame(cv::Mat frame){
//   while(true)
//   {
//       char c = (char)cv::waitKey(10);

//       // Press q to exit from window
//       if( c == 27 || c == 'q' || c == 'Q' )
//           break;

//       imshow("Cam",frame);
//   }
//}

//void runwebcam(){
//   cv::VideoCapture capture;
//   cv::Mat frame;

//   if (capture.isOpened())
//   {
//       while(true)
//       {
//           capture >> frame;
//           if(frame.empty())
//               break;

//           char c = (char)cv::waitKey(10);

//           // Press q to exit from window
//           if( c == 27 || c == 'q' || c == 'Q' )
//               break;

//           imshow("Cam",frame);
//       }
//   }else
//   {
//       std::cout << "Could not open camera";
//   };
//}

//void draw(cv::Mat& img, std::vector<cv::Rect> faces,double scale,int margin)
//{

//    for (size_t i = 0; i < faces.size(); i++)
//    {
//        cv::Rect r = faces[i];
//        cv::Mat smallImgROI;
//        cv::Scalar color = cv::Scalar(255, 0, 0); // Color for Drawing
//        rectangle(img, cv::Point(cvRound(r.x*scale-margin), cvRound(r.y*scale-margin)),
//                    cv::Point(cvRound((r.x + r.width-1)*scale+margin),
//                    cvRound((r.y + r.height-1)*scale+margin)), color, 3, 8, 0);
//    }
//}

//void runCascadeFace(std::string path){
//   cv::VideoCapture capture;
//   cv::Mat frame, image;

//   cv::CascadeClassifier cascade;
//   double scale=5;

//   cascade.load(path);

//   capture.open(0);
//   if (capture.isOpened())
//   {
//       while(true)
//       {
//           capture >> frame;
//           if(frame.empty())
//               break;
//           cv::Mat frame1 = frame.clone();
//           std::vector<cv::Rect> faces = detect(frame1,cascade,scale);
//           draw(frame1,faces,scale,50);
//           char c = (char)cv::waitKey(10);

//           // Press q to exit from window
//           if( c == 27 || c == 'q' || c == 'Q' )
//               break;

//           imshow("Cam",frame1);
//       }
//   }
//   else {std::cout<<"Could not Open Camera";}

//}
////////////////////
