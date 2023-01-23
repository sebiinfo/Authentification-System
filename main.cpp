#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include <dirent.h>
#include "cascade_conformity.hpp"
#include <string>
#include "localizer_cascade.hpp"

// Yassine = 0;
// Romain = 1;

#define test 5

#if test==5

void test_dir(std::string folder)
{
	DIR *dir;
	struct dirent *ent;
	dir = opendir(folder.c_str());
	Cascade_Localizer loc = Cascade_Localizer("Fancy");
	while ((ent = readdir(dir)) != nullptr)
	{
		std::string fileName = ent->d_name;
		if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".jpg")
		{
			cv::Mat frameclosed = cv::imread(folder + "/" + fileName);
			std::vector<cv::Mat> images = loc.Transform(frameclosed);

			for (int i = 0; i < images.size(); i++)
			{
				if(images[i].empty()){
					return;
				}
				cv::imshow(fileName, images[i]);
				cv::waitKey(0);
			}
		}
	}
	closedir(dir);
}

int main()
{

	std::string folder = "/Users/florencepoggi/Documents/Romain/Education/Bachelor X/Courses/Semester 3/CSE 201 - CPP/Project/Authentification-System/images/";
	std::string name = "Testing/";

	test_dir(folder + name);
	return 0;
}

#elif test == 3

int main()
{

    std::string path = "/Users/florencepoggi/Documents/Romain/Education/Bachelor X/Courses/Semester 3/CSE 201 - CPP/Project/Authentification-System/images/";
    std::string folder = "Testing/";
    std::string name = "agatha";
    std::string open = "open.jpg";
    std::string closed = "closed.jpg";

    std::string img_open = path + folder + name + open;

    cv::Mat image_open = cv::imread(img_open);

    int h, w;
    w = image_open.cols;
    h = image_open.rows;

    cv::imshow(" image1", image_open);

    cv::waitKey(0);

    cv::Rect crop_region(0, 20, w - 200, h - 400);

    image_open = image_open(crop_region);

    cv::imshow(" image1", image_open);

    cv::waitKey(0);

    return 0;
}

#elif test == 2

int main()
{

    std::string path = "./images/";
    std::string folder = "Testing/";
    std::string name = "sophie";
    std::string open = "open.jpg";
    std::string closed = "closed.jpg";

    std::string img_open = path + folder + name + open;
    std::string img_closed = path + folder + name + closed;

    cv::Mat image_open = cv::imread(img_open);
    cv::Mat image_closed = cv::imread(img_closed);

    Cascade_Localizer Loc = Cascade_Localizer("no_name", 244, 244, 10);

    std::vector<cv::Mat> images_open = Loc.Transform(image_open);
    std::vector<cv::Mat> images_closed = Loc.Transform(image_closed);

    for (int i = 0; i < images_open.size(); i++)
    {
        cv::imshow(" image1", images_open[i]);

        cv::waitKey(0);
    }

    for (int i = 0; i < images_closed.size(); i++)
    {
        cv::imshow(" image1", images_closed[i]);

        cv::waitKey(0);
    }
}

#elif test == 0
int testtransform()
{ // Tests Transform
    DIR *dir;
    struct dirent *ent;
    std::string folder = "..\\images\\Testing";
    dir = opendir(folder.c_str());
    while ((ent = readdir(dir)) != nullptr)
    {
        std::string fileName = ent->d_name;
        if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".jpg")
        {
            Cascade_Localizer loc = Cascade_Localizer("fancy");
            cv::Mat frameclosed = cv::imread(folder + "//" + fileName);
            std::vector<cv::Mat> faces = loc.Transform(frameclosed);
            if (faces.size() != 0)
            {
                std::cout << fileName << "  eyes detected";
                for (int i = 0; i < faces.size(); i++)
                {
                    cv::Mat eyeROI = frameclosed(faces[i]);
                    cv::imshow("eyeROI", eyeROI);
                    cv::waitKey(0);
                }
            }
            else
            {
                std::cout << fileName << "  eyes closed and not returned" << std::endl;
            }
        }
    }
    closedir(dir);
    return 0;
}

int testdetectmultiscale()
{ // Tests DetectMultiScale that filters the faces
    DIR *dir;
    struct dirent *ent;
    std::string folder = "..\\images\\Testing";
    dir = opendir(folder.c_str());
    while ((ent = readdir(dir)) != nullptr)
    {
        std::string fileName = ent->d_name;
        if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".jpg")
        {
            Cascade_Localizer loc = Cascade_Localizer("fancy");
            cv::Mat frameclosed = cv::imread(folder + "//" + fileName);
            std::vector<cv::Rect> eyes;
            loc.Rescale(frameclosed);
            loc.cascade->detectMultiScale(frameclosed, eyes, 1.06, 4, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
            if (eyes.size() != 0)
            {
                std::cout << fileName << "  eyes detected";
                for (int i = 0; i < eyes.size(); i++)
                {
                    cv::Mat eyeROI = frameclosed(eyes[i]);
                    cv::imshow("eyeROI", eyeROI);
                    cv::waitKey(0);
                }
            }
            else
            {
                std::cout << fileName << "  eyes closed and not returned" << std::endl;
            }
        }
    }
    closedir(dir);
    return 0;
}

int testeyedetection()
{ // Tests isEyeOpen function on the folder "Testing"
    DIR *dir;
    struct dirent *ent;
    std::string folder = "..\\images\\Testing";
    dir = opendir(folder.c_str());
    double trueclosed = 0;
    double falseclosed = 0;
    double falseopen = 0;
    double trueopen = 0;
    double count = 0;
    while ((ent = readdir(dir)) != nullptr)
    {
        std::string fileName = ent->d_name;
        if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".jpg")
        {
            count += 1;
            Cascade_Localizer loc = Cascade_Localizer("fancy");
            cv::Mat frameclosed = cv::imread(folder + "//" + fileName);
            std::vector<cv::Rect> eyes;
            loc.Rescale(frameclosed);
            bool eyeOpen0 = loc.cascade->EyedetectMultiScale(frameclosed, eyes, 1.06, 4, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
            for (int i = 0; i < eyes.size(); i++)
            {
                cv::Mat eyeROI = frameclosed(eyes[i]);
                cv::imshow("eyeROI", eyeROI);
                cv::waitKey(0);
            }
            if (fileName.find("closed") != std::string::npos) {
                if(eyeOpen0==0){
                    trueclosed+=1;
                }
                else
                {
                    falseclosed += 1;
                }
            }
            if (fileName.find("open") != std::string::npos)
            {
                if (eyeOpen0 == 1)
                {
                    trueopen += 1;
                }
                else
                {
                    falseopen += 1;
                }
            }
            std::cout << "file: " << fileName << "   status: " << eyeOpen0 << std::endl;
        }
    }
    closedir(dir);
    std::cout << std::endl;
    std::cout << "Total number of test images:   " << count << std::endl;
    std::cout << "True openeyes: " << trueopen << std::endl;
    std::cout << "Non detected openeyes: " << falseopen << std::endl;
    std::cout << "True closedeyes:  " << trueclosed << std::endl;
    std::cout << "Non detected closedeyes: " << falseclosed << std::endl;
    std::cout << "Total correct cases:  " << trueopen + trueclosed << "/" << count << " = " << ((trueopen + trueclosed) / count) * 100 << "%" << std::endl;
    return 0;
}

int test_angle_single_image() {
    cv::Mat image = cv::imread("..\\images\\Testing\\yassinetiltedopen2.jpg");
    Cascade_Localizer loc = Cascade_Localizer("fancy");
    loc.Rescale(image);
    cv::imshow("tilted",image);
    cv::waitKey(0);

    std::vector<cv::Rect> eyes;
    loc.cascade->EyedetectMultiScale(image, eyes, 1.06, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
    double angle = loc.get_angle_from_eyes(eyes);
    loc.rotate_face(image, angle);
    cv::imshow("img", image);
    cv::waitKey(0);
//    std::vector<cv::Mat> mats =loc.Transform(image);
//    std::cout<<mats.size();
//    for (int i=0; i<mats.size();i++){
//        cv::imshow("img",mats[i]);
//        cv::waitKey(0);
//    }

//int test_angle() {
//    DIR* dir;
//    struct dirent* ent;
//    std::string folder ="..\\images\\Team\\Tilted";
//    dir = opendir(folder.c_str());
//    while ((ent = readdir(dir)) != nullptr) {
//        std::string fileName = ent->d_name;
//        if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".jpg") {
//            cv::Mat image_open = cv::imread(folder + "//" + fileName);
//            Cascade_Localizer loc= Cascade_Localizer("fancy");
//            std::vector<cv::Rect> eyes;
//            loc.cascade->detectMultiScale(image_open,eyes, 1.06, 4, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
//            double angle = loc.get_angle_from_eyes(eyes);
//            loc.rotate_face(image_open,angle);
//            cv::imshow(fileName,image_open);
//
////            std::cout<<"file: "<<fileName<< "   status: " << angle <<std::endl;
////for(int i=0; i<images.size();i++){
////
////            cv::imshow(fileName,images[i]);
////            cv::waitKey(0);
////}
//        }
//    }
//    closedir(dir);
//    return 0;
//}
}

int main(){
//    testtransform();
//testeyedetection();
//     testdetectmultiscale();
    test_angle_single_image();
//    test_angle();

    return 0;
}

/// Users/florencepoggi/Documents/Romain/Education/Bachelor X/Courses/Semester 3/CSE 201 - CPP/Project/Authentification-System/images/Team
//    test_open_eye(image_path);

#elif test == 1
int main()
{

    return 0;
}

#endif
