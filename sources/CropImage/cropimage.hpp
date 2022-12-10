#ifndef CROPIMAGE_HPP
#define CROPIMAGE_HPP

#endif // CROPIMAGE_HPP

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>


//                                "                                       #
//   mmm    m mm   mmm   mmmm   mmm    mmmmm   mmm    mmmm   mmm          # mm   mmmm   mmmm
//  #"  "   #"  " #" "#  #" "#    #    # # #  "   #  #" "#  #"  #         #"  #  #" "#  #" "#
//  #       #     #   #  #   #    #    # # #  m"""#  #   #  #""""         #   #  #   #  #   #
//  "#mm"   #     "#m#"  ##m#"  mm#mm  # # #  "mm"#  "#m"#  "#mm"    #    #   #  ##m#"  ##m#"
//                       #                            m  #                       #      #
//                       "                             ""                        "      "


using namespace cv;
using namespace std;

void cropOne (Mat& image, int botLeft, int botRight, int topLeft, int topRight);
// Crops in place the image at given coordinates (bottom left, bottom right, top left, top right)

Mat getFrame();
// Get one frame from the webcam

void showFrame(Mat image);
// Displays the frame given as input.

void runwebcam();
// Opens the computer's webcam

void draw(Mat& img, vector<Rect> faces,double scale,int margin);
//draws the rectangles on the image given as input

vector<Rect> detect(Mat& img, CascadeClassifier& cascade, double scale);

void runCascadeFace(string path);
// Continuously detetcs a face using the xml at the given path

vector<Mat> cropWithRect(Mat frame, vector<Rect> faces);
// Returns a list of Mat of the faces detected from the frame given

vector<Mat> crop(Mat frame,string path);
// Returns a list of Mat cropped around the face recogised by the harrcascade file linked by the path

void showCrop(Mat frame,string path);
// Shows the images cropped from the photo
