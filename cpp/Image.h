#ifndef IMAGE
#define IMAGE

#include <boost/filesystem.hpp>
#include <opencv2/opencv.hpp>

#include "config.h"

class Image
{
public:
    Image(boost::filesystem::path filename, bool silent=false);

    /**
     * Add the HSV patches of this image to the given 0xM Matrix (increasing its row count)
     */
    void loadPatches(cv::Mat &into) const;

    /**
     * For every patch, find the most appropriate visual word and increase that bin in the given histogram
     *
     * Returns true if the image was added succesfully (may return false for an non-image)
     */
    bool loadVisualWords(cv::Mat &into, const cv::Mat &visualWords) const;
private:
    boost::filesystem::path m_filename;
    bool m_silent;

    void addHistogram(cv::Mat &into, const cv::Mat &patch) const;

    /**
     * Classify the given patch according to the given vocabulary
     *
     * Returns the index of the closest visual word in the given list.
     */
    int classifyPatch(const cv::Mat &patch, const cv::Mat &visualWords) const;
};

#define PATCHES_MATRIX(NAME) Mat NAME(0, HSV_PATCH_LENGTH, CV_32F)

#endif
