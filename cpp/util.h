#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <opencv2/opencv.hpp>
#include <cstdlib>

#define EQ(x, y) (abs(x - y) < 0.0001)

std::string matrixType(cv::Mat);

#endif
