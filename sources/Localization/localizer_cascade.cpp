#include "localizer_cascade.hpp"
#include "localizer.hpp"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <string>

Cascade_Localizer::Cascade_Localizer() : Cascade_Localizer(224, 224) {}

Cascade_Localizer::Cascade_Localizer(int w) : Cascade_Localizer(w, w) {}

Cascade_Localizer::Cascade_Localizer(int w,int h) : Localizer(w, h) {
    cascade.load("/usr/local/share/opencv4/haarcascades/haarcascade_frontalcatface.xml");
}

Cascade_Localizer::~Cascade_Localizer() {}


void Cascade_Localizer::localize_rect(cv::Mat & image, std::vector<cv::Rect> & faces) {
    cascade.detectMultiScale(image, faces, 1.1, 2, 0, cv::Size(30, 30));
}


bool Cascade_Localizer::is_pad(cv::Mat image, cv::Rect face)
{
    int padx, pady,boundx, boundy;
    int w,h;
    boundx = image.cols;
    boundy = image.dims;

    w = face.width;
    h = face.height;
    padx = round ( (1+padding/100) * w);
    pady = round ( (1+padding/100) * h);

    if(face.x-padx < 0){return false;} // Left side

    if(face.x+w+padx > boundx){return false;} // Right side

    if(face.y-pady < 0){return false;} // Bottom side

    if(face.y+h+pady > boundy){return false;} // Top side

    return true;
}
void Cascade_Localizer::Crop_(cv::Mat &image,cv::Rect face)
{
    int w,h,x,y;
            w = face.width;
            h = face.height;
            x = face.x;
            y = face.y;
        if (!is_pad(image,face))
            {
                image = image(cv::Range(y,y+h), cv::Range(x,x+h));
                return;
            }

            int padx = round(w *(1+ padding / 100));
            int pady = round(h *(1+ padding / 100));

            image = image(cv::Range(y-pady,y+h+pady), cv::Range(x-padx,x+h+padx));

}

std::vector<cv::Mat> Cascade_Localizer::Crop(cv::Mat image,std::vector<cv::Rect> faces)
{
    std::vector<cv::Mat> face_array;
        cv::Mat face;

        for (size_t i = 0; i < faces.size(); i++)
        {

            face = image.clone();
            Crop_(face,faces[i]);

            face_array.push_back(face.clone());

        };
        return face_array;
    }

void Cascade_Localizer::Rescale(cv::Mat &image)
{
    cv::Mat resized(height, width, image.type());

        double scale_factor_x = (double)width / image.cols;
        double scale_factor_y = (double)height / image.rows;

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                double originalx = x / scale_factor_x;
                double originaly = y / scale_factor_y;

                // Compute the weights for the four nearest pixels
                double weightx = originalx - floor(originalx);
                double weighty = originaly - floor(originaly);

                double w1 = (1 - weightx) * (1 - weighty);
                double w2 = weightx * (1 - weighty);
                double w3 = (1 - weightx) * weighty;
                double w4 = weightx * weighty;

                // Get the pixel values of the four nearest pixels
                cv::Vec3b p1 = image.at<cv::Vec3b>(floor(originaly), floor(originalx));
                cv::Vec3b p2 = image.at<cv::Vec3b>(floor(originaly), ceil(originalx));
                cv::Vec3b p3 = image.at<cv::Vec3b>(ceil(originaly), floor(originalx));
                cv::Vec3b p4 = image.at<cv::Vec3b>(ceil(originaly), ceil(originalx));

                //Use the weights to compute the pixel values
                cv::Vec3b pixel;
                for (int i = 0; i < 3; i++)
                {
                    pixel[i] = (unsigned char)(w1 * p1[i] + w2 * p2[i] + w3 * p3[i] + w4 * p4[i]);
                }

                // Set the pixel value in the resized image
                resized.at<cv::Vec3b>(y, x) = pixel;
            }
        }
        image= resized;
}

void Cascade_Localizer::Rescale(std::vector<cv::Mat> &images)
{
    for (int i=0; i<images.size();i++)
        {
           Rescale(images[i]);
        }
}


std::vector<cv::Mat> Cascade_Localizer::Transform(cv::Mat image,std::vector<cv::Rect> faces)
{
    assert(false);

}





















