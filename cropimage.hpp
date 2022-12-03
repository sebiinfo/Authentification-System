#ifndef CROPIMAGE_HPP
#define CROPIMAGE_HPP

#endif // CROPIMAGE_HPP

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

using namespace cv;
using namespace std;

void inplaceCrop (Mat image, int botLeft, int botRight, int topLeft, int topRight);
// Crops in place the image at given coordinates (bottom left, bottom right, top left, top right)

void runwebcam();
// Opens the computer's webcam

Mat getFrame();
// Get one frame from the webcam

void showFrame(Mat,string);
// Displays the frame given as input with window title name, "Frame" by default

Mat Crop(Mat image, int botLeft, int botRight, int topLeft, int topRight);
// Returns a cropped version of the image without modifying it at coordinates (bottom left, bottom right, top left, top right)

vector<Rect> CoordFace(Mat image,string pathname,double scale,Size size);
// returns a potential position of a face in the image using the haarcascade xml file at path, using in min size Size

void detectface(Mat frame,string path,double scale,Size size=Size(50,50),Scalar drawColor = Scalar(255,0,0));
// Detects and displays the face on the frame using the haarcascade at path,
// scaling the image by scale if the face is of size at least size using the color drawColor

void runCascadeFace(string path);
// Continuously detetcs a face using the xml at the given path
