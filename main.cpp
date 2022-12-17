#include <iostream>

#include <opencv2/core/mat.hpp>
#include "cropimage.hpp"
#include "Facedata.hpp"
#include "rescale.hpp"
using namespace std;

using namespace cv;
int main() {
    Mat image = imread("C:\\Users\\USER\\CLionProjects\\Authentification-System\\image.jpg");
    Mat resizedImage = rescaleImage(image, 224, 224);
    imwrite("C:\\Users\\USER\\CLionProjects\\Authentification-System\\imageout.jpg", resizedImage);

}
