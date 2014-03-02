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
     * Load the features for all patches into the given feature matrix.
     *
     * Adds a row for every patch.
     */
    void loadFeatures(cv::Mat &into) const;

    /**
     * Load the visual words for all patches into the given visual words matrix.
     *
     * Adds a row for the entire image that, for every visual word, contains
     * the count of patches in this image that are closest to that visual word.
     *
     * The row is normalized (i.e., all of the weights add up to 1).
     *
     * Returns true if the image was added succesfully (may return false for an
     * non-image).
     */
    bool loadVisualWords(cv::Mat &into, const cv::Mat &visualWords) const;

    boost::filesystem::path filename() const { return m_filename; }
private:
    boost::filesystem::path m_filename;
    bool m_silent;

    /**
     * Extract a feature vector out of the patch, and add it to the 'into'
     * matrix as a row, which will have FEATURE_VECTOR_LENGTH columns.
     */
    void extractFeatures(cv::Mat &into, const cv::Mat &patch) const;

    /**
     * Return the closest visual word for the given feature vector.
     */
    int classifyWord(const cv::Mat &features, const cv::Mat &visualWords) const;
};

// Macro for definining a feature matrix
#define FEATURE_MATRIX(NAME) Mat NAME(0, FEATURE_VECTOR_LENGTH, CV_32F)

#endif
