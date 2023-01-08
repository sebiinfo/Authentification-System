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
            count+=1;
            std::string fileName = ent->d_name;
            if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".jpg") {
                cv::Mat frameclosed = cv::imread(folder+"//"+fileName);
                //normalizeIntensities(frameclosed);
                frameclosed=rescaleImage(frameclosed, 224,224);
                bool eyeOpen0 = detectEyes(frameclosed);
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
        std::cout<<"False openeyes: "<<falseopen<<std::endl;
        std::cout<<"True closedeyes:  "<<trueclosed<<std::endl;
        std::cout<<"False openeyes: "<<falseclosed<<std::endl;
        std::cout << "Total correct cases:  "<<trueopen+trueclosed<<"/"<<count<<" = "<<((trueopen+trueclosed)/count)*100<<"%"<<std::endl;
    return 0;
    }

