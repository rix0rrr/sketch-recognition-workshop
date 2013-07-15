#include "ImageClass.h"

using namespace cv;

ImageClass::ImageClass(std::string label) : m_label(label)
{
}

void ImageClass::include(boost::filesystem::path filename)
{
    m_images.push_back(Image(filename));
}

void ImageClass::loadPatches(Mat &into)
{
    typedef std::vector<Image>::iterator iter;

    for (iter it = m_images.begin(); it != m_images.end(); it++)
    {
        it->loadPatches(into);
    }
}
