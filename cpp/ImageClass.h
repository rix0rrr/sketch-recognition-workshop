#ifndef IMAGECLASS_H
#define IMAGECLASS_H

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <boost/filesystem.hpp>

#include "Image.h"

class ImageClass {
public:
    ImageClass(std::string label);

    void include(boost::filesystem::path filename);

    void loadPatches(cv::Mat &into);
private:
    std::string m_label;
    std::vector<Image> m_images;
};

#endif
