#include "localizer_cascade.hpp"
#include "localizer.hpp"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/base.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include "../Cascade/cascade_detect_cv.hpp"
#include <string>
const double pi = 3.14159265358979323846;

Cascade_Localizer::Cascade_Localizer() : Cascade_Localizer(224) {}

Cascade_Localizer::Cascade_Localizer(int w) : Cascade_Localizer(w, 10) {}

Cascade_Localizer::Cascade_Localizer(int w,int pad) : Cascade_Localizer(w, w,pad) {}


Cascade_Localizer::Cascade_Localizer(int w, int h, int pad){ 
    Localizer (w, h, pad);
    cascade = Cascade_detect_cv();
//   cascade.load("/usr/local/share/opencv4/haarcascades/haarcascade_frontalface_default.xml");
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

double Cascade_Localizer::get_angle_from_eyes(cv::Mat image, std::vector<cv::Rect> &faces, std::vector<cv::Rect> eyes) {

    int x, y, w, h;
    for (int i = 0; i < faces.size(); i++)
    {
        x = faces[i].x;
        y = faces[i].y;
        w = faces[i].width;
        h = faces[i].height;
//        cv::rectangle(image, cv::Point(x, y), cv::Point(x + w, y + h), cv::Scalar(0, 255, 0), 2);
//        cv::circle(image, cv::Point(x + int(w * 0.5), y + int(h * 0.5)), 4, cv::Scalar(0, 255, 0), -1);
    }
    int index = 0;
    cv::Rect eye_1(0, 0, 0, 0);
    cv::Rect eye_2(0, 0, 0, 0);
    for (int i = 0; i < eyes.size(); i++)
    {
        if (index == 0)
        {
            eye_1 = eyes[i];
        }
        else if (index == 1)
        {
            eye_2 = eyes[i];
        }
        index++;
    }
    if (eye_1.x != 0 && eye_2.x != 0)
    {
        cv::Rect left_eye;
        cv::Rect right_eye;
        if (eye_1.x < eye_2.x)
        {
            left_eye = eye_1;
            right_eye = eye_2;
        }
        else
        {
            left_eye = eye_2;
            right_eye = eye_1;
        }
        cv::Point left_eye_center = cv::Point(left_eye.x + (left_eye.width / 2),
                                              left_eye.y + (left_eye.height / 2));
        cv::Point right_eye_center = cv::Point(right_eye.x + (right_eye.width / 2),
                                               right_eye.y + (right_eye.height / 2));
        double left_eye_x = left_eye_center.x;
        double left_eye_y = left_eye_center.y;
        double right_eye_x = right_eye_center.x;
        double right_eye_y = right_eye_center.y;
        double delta_x, delta_y;
        delta_x = right_eye_x - left_eye_x;
        delta_y = right_eye_y - left_eye_y;
        double angle;
        if (delta_x==0 || delta_y==0){
            angle=0;
        }
        else {
            double angle_rad = std::atan(delta_y / delta_x);
            angle = (angle_rad * 180) / pi;
        }
        return angle;
    }
    return 0;
}

cv::Mat Cascade_Localizer::rotate_face(cv::Mat image, std::vector<cv::Rect> &faces, double angle)
{
    //    cv::Size s= image.size();
    //    double height =s.height;
    //    double width = s.width;
    if(-10<angle<10){
        return image;
    }
    int height, width;
    height = image.rows;
    width = image.cols;
    cv::Point2f image_center = cv::Point(height / 2, width / 2);
    cv::Mat rotation_mat = cv::getRotationMatrix2D(image_center, angle, 1);
    double abs_cos = abs(cos(angle));
    double abs_sin = abs(sin(angle));
    int bound_w = height * abs_sin + width * abs_cos;
    int bound_h = height * abs_cos + width * abs_sin;
    rotation_mat.at<double>(0, 2) += bound_w / 2 - image_center.x;
    rotation_mat.at<double>(1, 2) += bound_h / 2 - image_center.y;
    cv::warpAffine(image, image, rotation_mat, cv::Size(bound_w, bound_h));
    cascade.detectMultiScale(image, faces,  1.06, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

}


std::vector<cv::Mat> Cascade_Localizer::Transform(cv::Mat image,std::vector<cv::Rect> faces)
{
    std::vector<cv::Mat> out;

    cascade.Special_Transform();

    out = Crop(image,faces);
    Rescale(out);

    return out;

}















