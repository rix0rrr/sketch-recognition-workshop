#include "ImageClass.h"
#include <algorithm>
#include <ctime>

using namespace cv;

int ImageClass::s_counter = 0;

ImageClass::ImageClass(std::string label) : m_label(label)
{
    m_intLabel = ++s_counter;
}

void ImageClass::include(boost::filesystem::path filename)
{
    m_images.push_back(Image(filename));
}

void ImageClass::shuffle()
{
    std::random_shuffle(m_images.begin(), m_images.end());
}

void ImageClass::loadPatches(Mat &into)
{
    for (ImageList::iterator it = m_images.begin(); it != m_images.end(); it++)
    {
        it->loadPatches(into);
    }
}

void ImageClass::loadVisualWords(cv::Mat &intoWords, cv::Mat &intoLabels, const cv::Mat &vocabulary)
{
    for (ImageList::iterator it = m_images.begin(); it != m_images.end(); it++)
    {
        if (it->loadVisualWords(intoWords, vocabulary))
        {
            intoLabels.push_back(Vec<int, 1>(m_intLabel));
        }
    }
}

void ImageClass::remove(int start_index, int end_index)
{
    m_images.erase(m_images.begin() + start_index, m_images.begin() + end_index);
}
