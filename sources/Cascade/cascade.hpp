#include <opencv2/opencv.hpp>
#include <vector>

class Cascade
{
public:

Cascade(); // Contructor initialize with 244x244 dimension, 10% padding, no image and no special cascade.

Cascade(int w,int h,int pad,cv::Mat img); // Initialize with specific dims
Cascade(cv::Mat img); // Give image with default size

~Cascade(); // Destructor


private: // Private methods only used inside the class

std::vector<cv::Rect> CoordCascade();


cv::Mat Crop(cv::Rect rect); // Crops the image using coordinates given with padding
bool is_pad (cv::Mat image, cv::Rect face,int pad); // Returns true if we can add a padding of pad %

std::vector<cv::Mat> cropArray (cv::Mat image, std::vector<cv::Rect> faces_rect);

void Tilt(); // Tilt the image so it is horizontal, it uses the eyes detection
//double rotate_face(cv::Mat &image);
//cv::Mat rotate_face_aux(cv::Mat &image, double angle);

cv::Mat Resize(cv::Mat img); // Resizes the image given to the dimensions set by the class attribute

public: // Methods that can be accessed from outside the class ( on the object )

cv::Mat Transform(); // Transforms and returns the image attribute in the proper form for the algorithm

//bool isFace(cv::Mat frame);
//bool isEye(cv::Mat);
bool Conform(); // Check if the image is in the proper format for transformation: if eyes are open, padding fits

////////////////////////////////////////////
// Methods to access the class attributes //
////////////////////////////////////////////

void set_image(cv::Mat img); // Change image
void get_image(cv::Mat img); // Get the image of the class

void set_width(int w); // Changes the width of the image detected
int get_width(); // Get the width of the image after the transformation

void set_height(int h); // Changes the height of the image detected
int get_height(); // Get the height of the image after the transformation

void set_padding(int pad); // Changes the padding of the image detected
int get_padding(); // Get the padding of the image after the transformation

cv::CascadeClassifier get_face_cascade(); // get the classifier used for face
cv::CascadeClassifier get_eye_cascade(); // get the classifier used for eye

void load_special_cascade(cv::CascadeClassifier cascade); // Set the special cascade
cv::CascadeClassifier get_special_cascade(); // get the special classifier

private:
    cv::Mat image; // The image we work on in the class
    cv::CascadeClassifier face_cascade; // The cascade we use for detection of face
    cv::CascadeClassifier eye_cascade; // The cascade we use for detection of eyes
    cv::CascadeClassifier special_cascade; // Special cascade used for detection of other than face/eyes or fancier face/eyes

    int width; // Width of the size of the image we want to trasnform
    int height; // Height of the size of the image we want to trasnform
    int padding; // Padding we will add when transforming

};
