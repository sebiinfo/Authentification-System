#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include <dirent.h>
//#include "tests.cpp"
#include "detect.hpp"
#include "rescale.hpp"
#include "sources/Cropimage/cropimage.hpp"
#include <string>
#include "localizer.hpp"

int testeyedetection(){ //Tests isEyeOpen function on the folder "Testing"
    // Please name every picture you add with the word closed or open.
    DIR* dir;
    struct dirent* ent;
    std::string folder ="C:\\Users\\USER\\CLionProjects\\Authentification-System\\Authentification-System\\images\\Testing";
    dir = opendir(folder.c_str());
    double trueclosed=0;
    double falseclosed=0;
    double falseopen=0;
    double trueopen=0;
    double count=0;
    while ((ent = readdir(dir)) != nullptr) {
        std::string fileName = ent->d_name;
        if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".jpg") {
            count+=1;
            cv::Mat frameclosed = cv::imread(folder+"//"+fileName);
            //normalizeIntensities(frameclosed);
            frameclosed=rescaleImage(frameclosed, 224,224);
            bool eyeOpen0 = isEyeOpen(frameclosed);
            if (fileName.find("closed") != std::string::npos) {
                if(eyeOpen0==0){
                    trueclosed+=1;
                }
                else{
                    falseclosed+=1;
                }
            }
            if (fileName.find("open") != std::string::npos) {
                if(eyeOpen0==1){
                    trueopen+=1;
                }
                else{
                    falseopen+=1;
                }
            }
            std::cout<<"file: "<<fileName<< "   status: " << eyeOpen0<<std::endl;
        }
    }
    closedir(dir);
    std::cout<<std::endl;
    std::cout<<"Total number of test images:   "<<count<<std::endl;
    std::cout<<"True openeyes: "<<trueopen<<std::endl;
    std::cout<<"Non detected openeyes: "<<falseopen<<std::endl;
    std::cout<<"True closedeyes:  "<<trueclosed<<std::endl;
    std::cout<<"Non detected closedeyes: "<<falseclosed<<std::endl;
    std::cout << "Total correct cases:  "<<trueopen+trueclosed<<"/"<<count<<" = "<<((trueopen+trueclosed)/count)*100<<"%"<<std::endl;
    return 0;
}

void showFrame(cv::Mat frame){
   while(true)
   {
       char c = (char)cv::waitKey(10);

       // Press q to exit from window
       if( c == 27 || c == 'q' || c == 'Q' )
           break;

       imshow("Cam",frame);
   }
}


cv::Mat getFrame(){
   cv::VideoCapture cap(0);
   if (!cap.isOpened()){
       return cv::Mat();
   };
   cv::Mat frame;
   cap >> frame;
   return frame;
}

int main(){
//    testeyedetection();
    std::string root, name, path;
    cv::Mat image;

#define CAMERA 0

#if CAMERA == 1

    image = getFrame();

#else

    root = "/Users/florencepoggi/Documents/Romain/Education/Bachelor X/Courses/Semester 3/CSE 201 - CPP/Project/Authentification-System/images";
    name = "/Testing/agathaopen.jpg";
    path = root.append(name);

    image = cv::imread(path);

#endif




    std::cout << image.size() << std::endl;

    Localizer loc = Localizer();
    std::vector<cv::Mat> crops = loc.localize(image);

    cv::Mat out = crops[0];

//    std::cout << out.size() << std::endl;

    showFrame(out);
    return 0;
}


void test_open_eye(std::string image_path)
{
    cv::Mat image = cv::imread(image_path);
    if (conform(image)){
//        std::cout << image_path.substr(0,13)<< ": is conform";
    }else{
        std::cout << "Image not conform";
    }
}



///Users/florencepoggi/Documents/Romain/Education/Bachelor X/Courses/Semester 3/CSE 201 - CPP/Project/Authentification-System/images/Team
//    test_open_eye(image_path);

