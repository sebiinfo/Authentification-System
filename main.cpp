#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include <dirent.h>
//#include "tests.cpp"
#include "detect.hpp"
#include "rescale.hpp"
#include "cascade_conformity.hpp"
//#include "cropimage.hpp"
#include <string>
#include "localizer.hpp"

#include "localizer_cascade.hpp"


//Yassine = 0;
//Romain = 1;

#define test 0

#if test==2

int main()
{
	int w = 244;
	int h = 244;
	int pad = 10;

	std::string img_path = "/Users/florencepoggi/Documents/Romain/Education/Bachelor X/Courses/Semester 3/CSE 201 - CPP/Project/Authentification-System/images/Team/yassine.jpg";

	cv::Mat image = cv::imread(img_path);

	Cascade_Localizer Loc = Cascade_Localizer();


	std::cout << Loc.height << std::endl;
	std::cout << Loc.width << std::endl;
	std::cout << Loc.padding << std::endl;

	std::vector<cv::Rect> faces;

	Loc.cascade.detectMultiScale(image,faces,1,4,0,cv::Size(30,30));

	std::vector<cv::Mat> images = Loc.Transform(image,faces);

	std::cout << images.size() << std::endl;

}

#elif test == 0
//void testlocalizer()
//{
//
//    std::string folder ="C:\\Authentification-System\\images\\Testing\\agathaopen.jpg";
//
//    cv::Mat image;
//    image = cv::imread(folder);
//
//    Localizer loc = Localizer();
//
//    std::vector<cv::Mat> arr = loc.localize(image);
//
//    while (true){
//        cv::imshow("img",arr[0]);
//    }
//
//}


int testeyedetection(){ //Tests isEyeOpen function on the folder "Testing"
    //Please name every picture you add with the word closed or open.
    DIR* dir;
    struct dirent* ent;
    std::string folder ="C:\\Authentification-System\\images\\Testing";
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

int test_angle() {
    DIR* dir;
    struct dirent* ent;
    std::string folder ="C:\\Authentification-System\\images\\Testing";
    dir = opendir(folder.c_str());
    while ((ent = readdir(dir)) != nullptr) {
        std::string fileName = ent->d_name;
        if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".jpg") {
            cv::Mat frameclosed = cv::imread(folder+"//"+fileName);
            //normalizeIntensities(frameclosed);
            double angle;
            angle=rotate_face(frameclosed);
            std::cout<<"file: "<<fileName<< "   status: " << angle <<std::endl;
            cv::imshow(fileName,frameclosed);
            cv::waitKey(0);
        }
    }
    closedir(dir);
    return 0;
}

int test_conformity(){

    DIR* dir;
    struct dirent* ent;
    std::string folder ="C:\\Authentification-System\\images\\Testing";
    dir = opendir(folder.c_str());
    while ((ent = readdir(dir)) != nullptr) {
        std::string fileName = ent->d_name;
        if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".jpg") {
            Cascade_conformity Conform_faces=Cascade_conformity();
            cv::Mat frameclosed = cv::imread(folder+"//"+fileName);
            Conform_faces.Transform(frameclosed);
            cv::imshow(fileName,frameclosed);
            cv::waitKey(0);
            std::cout<< "Detected eyes:  "<<Conform_faces.isEye(frameclosed)<<std::endl;
            double angle;
            angle=Conform_faces.get_angle_from_eyes(frameclosed);
            Conform_faces.rotate_face(frameclosed,angle);
            std::cout<<"file: "<<fileName<< "   status: " << angle <<std::endl;
            cv::imshow(fileName+" modified",frameclosed);
            cv::waitKey(0);
        }
    }
    closedir(dir);
    return 0;

}


int test_loc(){
    {
        int w = 244;
        int h = 244;
        int pad = 10;

        std::string img_path = "../images/Team/yassine.jpg";

        cv::Mat image = cv::imread(img_path);

        Cascade_Localizer Loc = Cascade_Localizer();


        std::cout << Loc.height << std::endl;
        std::cout << Loc.width << std::endl;
        std::cout << Loc.padding << std::endl;

        std::vector<cv::Rect> faces;

        Loc.cascade.detectMultiScale(image,faces,1,4,0,cv::Size(30,30));

        std::vector<cv::Mat> images = Loc.Transform(image,faces);

        std::cout << images.size() << std::endl;

    }
}

int main(){
    test_conformity();
//    testeyedetection();
    //testlocalizer();

   //  test_angle();
//    cv::Mat image = cv::imread("C:\\Users\\USER\\CLionProjects\\Authentification-System\\Authentification-System\\images\\Testing\\yassinetiltedopen.jpg");
//    Localizer loc = Localizer();
//    std::vector<cv::Mat> crops = loc.localize(image);
//    cv::Mat out = crops[0];
//    cv::Mat rotate =rotate_face(out);
//    cv::imshow("img",rotate);
//    cv::waitKey(0);

//    std::string image_path = "Authentification_System/images/Team/yassine.jpg";
//    std::string path2 = "/Users/florencepoggi/Documents/Romain/Education/Bachelor X/Courses/Semester 3/CSE 201 - CPP/Project/Authentification-System/images/Team/yassine.jpg";
//    cv::Mat image = cv::imread(image_path);
//    while (true){
//           cv::imshow("img",image);
//    }
    return 0;
}


void test_open_eye(std::string image_path)
{
    cv::Mat image = cv::imread(image_path);
    if (conform(image)){
        std::cout << image_path.substr(0,13)<< ": is conform";
    }else{
        std::cout << "Image not conform";
    }
}



///Users/florencepoggi/Documents/Romain/Education/Bachelor X/Courses/Semester 3/CSE 201 - CPP/Project/Authentification-System/images/Team
//    test_open_eye(image_path);

#elif test ==1
int main()
{


    return 0;
}

#endif
