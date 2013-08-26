#ifndef HOGDESCRIPTOR_VISU_H
#define HOGDESCRIPTOR_VISU_H

#include <opencv2/opencv.hpp>
#include <vector>

cv::Mat get_hogdescriptor_visu(const cv::Mat& origImg, cv::Mat& histo, int patch_x, int patch_y);

#endif
