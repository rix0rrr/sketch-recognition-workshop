#ifndef IMAGECLASS_H
#define IMAGECLASS_H

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <boost/filesystem.hpp>

#include "Image.h"

typedef std::vector<Image> ImageList;

class ImageClass {
public:
    ImageClass(std::string label);

    void include(boost::filesystem::path filename);

    void loadPatches(cv::Mat &into);

    void shuffle();

    /**
     * Load the visual words-based representations of the images in this class
     *
     * For every image, adds a VW-based representation of the image to the intoWords matrix
     * and the (numbered) label of this class into the intoLabels matrix.
     */
    void loadVisualWords(cv::Mat &intoWords, cv::Mat &intoLabels, const cv::Mat &vocabulary); 

    void remove(int start_index, int end_index);
    int image_count() const { return m_images.size(); }
    std::string getLabel() const { return m_label; }
    int intLabel() const { return m_intLabel; }

    const ImageList &images() const { return m_images; }
private:
    static int s_counter;

    std::string m_label;
    int m_intLabel;
    ImageList m_images;
};

#endif
