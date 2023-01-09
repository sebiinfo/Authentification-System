#include "rescale.hpp"
#include <opencv2/core/mat.hpp>


cv::Mat rescaleImage(cv::Mat image, int newWidth, int newHeight)
// Rescales the image using bilinear interpolation and returns the resized image
{
    cv::Mat resized(newHeight, newWidth, image.type());
    //Compute the scaling factors
    double scale_factor_x = (double)newWidth / image.cols;
    double scale_factor_y = (double)newHeight / image.rows;

    for (int y = 0; y < newHeight; y++)
    {
        for (int x = 0; x < newWidth; x++)
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
    return resized;
}

std::vector<cv::Mat> rescaleArray (std::vector<cv::Mat> array,int w, int h)
{
    for (int i=0; i<array.size();i++)
    {
        array[i] = rescaleImage(array[i],w,h);
    }
    return array;
}
