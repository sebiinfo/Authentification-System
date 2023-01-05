#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

// Crops in place the image at given coordinates (bottom left, bottom right, top left, top right)
void cropOne(cv::Mat &image, int botLeft, int botRight, int topLeft, int topRight);

// Get one frame from the webcam
cv::Mat getFrame();

// Displays the frame given as input.
void showFrame(cv::Mat image);

void runwebcam();
// Opens the computer's webcam

// draws the rectangles on the image given as input
void draw(cv::Mat &img, std::vector<cv::Rect> faces, double scale, int margin);

// Returns a vector array of Rectangles holding the coordinates of faces recognised on the given image
std::vector<cv::Rect> detect(cv::Mat &img, cv::CascadeClassifier &cascade, double scale);

// Continuously detetcs a face using the xml at the given path
void runCascadeFace(std::string path);

// Returns a list of Mat of the faces detected from the frame given
std::vector<cv::Mat> cropWithRect(cv::Mat frame, std::vector<cv::Rect> faces);

// Returns a list of Mat cropped around the face recogised by the harrcascade file linked by the path
std::vector<cv::Mat> crop(cv::Mat frame, std::string path);

// Shows the images cropped from the photo
void showCrop(cv::Mat frame, std::string path);