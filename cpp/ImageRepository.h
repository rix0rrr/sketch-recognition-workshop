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

/**
 * Partition the input data set into two sets, respecting classes.
 *
 * The first set contains the given fraction of the total samples (0 <= oneFraction < 1)
 */
void partition(const ImageClassList &source, float fractionA, ImageClassList &targetA, ImageClassList &targetB);

#endif
