#ifndef IMAGES_H
#define IMAGES_H

#include <opencv2/opencv.hpp>
#include <boost/filesystem.hpp>

#include <memory>
#include <string>
#include <vector>

#include "ImageClass.h"

typedef std::vector<ImageClass> ImageClassList;

class ImageRepository
{
public:
    ImageRepository(std::string directory);

    ImageClassList classes();
private:
    std::string m_directory;

    ImageClass makeClass(boost::filesystem::path directory);
};

#endif
