#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
using namespace cv;
int main() {
   std::string image_path =
       "~/Desktop/Van_Gogh_-_Starry_Night_-_Google_Art_Project.jpg";
   Mat img = imread(image_path, IMREAD_COLOR);
   if (img.empty()) {
      std::cout << "Could not read the image: " << image_path << std::endl;
      return 1;
   }
   imshow("Display window", img);
   int k = waitKey(0);  // Wait for a keystroke in the window
   if (k == 's') {
      imwrite("starry_night.png", img);
   }

   waitKey(0);
   return 0;
}
