#ifndef IMAGE
#define IMAGE

#include <boost/filesystem.hpp>
#include <opencv2/opencv.hpp>

#include "config.h"

class Image
{
public:
    Image(boost::filesystem::path filename);

    void loadPatches(cv::Mat &into);
private:
    boost::filesystem::path m_filename;

    Patch makeHistogram(const cv::Mat &patch);
};

#endif
