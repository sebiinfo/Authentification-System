#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

// Crops in place the image at given coordinates (bottom left, bottom right, top left, top right)
void crop(cv::Mat &image, int botLeft, int botRight, int topLeft, int topRight);

// Crops an image using an array of cv::Rect
std::vector<cv::Mat> cropArray (cv::Mat image, std::vector<cv::Rect> faces_rect);

// Returns true if we can add a padding of pad %
bool is_pad (cv::Mat image, cv::Rect face,int pad);

// Crops an image with padding, if the padding is in the frame, if not, then crops without padding
void cropPad(cv::Mat& image,cv::Rect face,int pad);

// Returns a vector array of Rectangles holding the coordinates of faces recognised on the given image
//std::vector<cv::Rect> detect(cv::Mat &img, cv::CascadeClassifier &cascade, double scale);

// Returns a list of Mat of the faces detected from the frame given
//std::vector<cv::Mat> cropWithRect(cv::Mat frame, std::vector<cv::Rect> faces);

// Returns a list of Mat cropped around the face recogised by the harrcascade file linked by the path
//std::vector<cv::Mat> crop(cv::Mat frame, std::string path);

// Shows the images cropped from the photo
//void showCrop(cv::Mat frame, std::string path);

///////////////

 //// Get one frame from the webcam
// cv::Mat getFrame();

// //// Displays the frame given as input.
// void showFrame(cv::Mat image);

// //// Opens the computer's webcam
// void runwebcam();

// //// Continuously detetcs a face using the xml at the given path
// void runCascadeFace(std::string path);

// //// draws the rectangles on the image given as input
// void draw(cv::Mat &img, std::vector<cv::Rect> faces, double scale, int margin);
///////////////
