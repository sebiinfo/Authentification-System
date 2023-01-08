#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>
//#include "tests.cpp"
#include "detect.hpp"
#include "rescale.hpp"
#include "sources/Cropimage/cropimage.hpp"
#include <dirent.h>
#include <string>


int main(){
    DIR* dir;
    struct dirent* ent;
    std::string folder ="C:\\Users\\USER\\CLionProjects\\Authentification-System\\Authentification-System\\images\\Testing";
    dir = opendir(folder.c_str());
        while ((ent = readdir(dir)) != nullptr) {
            std::string fileName = ent->d_name;
            if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".jpg") {
                cv::Mat frameclosed = cv::imread(folder+"//"+fileName);
                //normalizeIntensities(frameclosed);
                frameclosed=rescaleImage(frameclosed, 224,224);
                bool eyeOpen0 = detectEyes(frameclosed);
                std::cout<<"file: "<<fileName<< "   status: " << eyeOpen0<<std::endl;
            }
        }
        closedir(dir);
    return 0;
    }

