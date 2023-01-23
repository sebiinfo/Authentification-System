#ifndef AUTHENTICATION_SYSTEM_CASCADE_CV_HPP
#define AUTHENTICATION_SYSTEM_CASCADE_CV_HPP

#include "localizer.hpp"
#include <opencv2/core/mat.hpp>
#include <opencv2/objdetect.hpp>
#include "../Cascade/cascade_Base.hpp"
#include <string>

class Cascade_Localizer : public Localizer
{
public:
  Cascade_Localizer();
  Cascade_Localizer(std::string cascade_chosen);
  Cascade_Localizer(std::string cascade_chosen, int w);
  Cascade_Localizer(std::string cascade_chosen, int w, int pad);
  Cascade_Localizer(std::string cascade_chosen, int w, int h, int pad);
  ~Cascade_Localizer();

  void change_Cascade_name(std::string cascade_chosen);
  std::string get_Cascade_name();
  void reload_cascade();

  void localize_rect(cv::Mat &image, std::vector<cv::Rect> &faces);

  std::vector<cv::Mat> Transform(cv::Mat image);
    double get_angle_from_eyes(std::vector<cv::Rect> eyes);
    void rotate_face(cv::Mat &image, double angle);
    void Rescale(cv::Mat &image);

  // Attribute //

  Cascade_base *cascade;

private:
  std::string Cascade_name;

  bool is_pad(cv::Mat image, cv::Rect face);

  void Crop_(cv::Mat &image, cv::Rect face);
  std::vector<cv::Mat> Crop(cv::Mat image, std::vector<cv::Rect> faces);


  void Rescale(std::vector<cv::Mat> &images);



  void recheck(std::vector<cv::Mat> &images);
};

#endif // AUTHENTICATION_SYSTEM_CASCADE_CV_HPP
