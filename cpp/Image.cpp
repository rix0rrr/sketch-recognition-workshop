#include <algorithm>
#include <iostream>
#include <limits>
#include <cassert>

#include "util.h"
#include "Image.h"
#include "rgb_to_hsv.h"

using namespace cv;
using namespace std;

Image::Image(boost::filesystem::path filename, bool silent) : m_filename(filename), m_silent(silent)
{
}

void Image::loadPatches(Mat &into) const
{
    if (!m_silent) cout << m_filename.string() << endl;

    Mat image = cvLoadImage(m_filename.string().c_str(), CV_LOAD_IMAGE_COLOR);
    if (image.data == NULL) return;

    for (int y = 0; y < image.size().height - PATCH_SIZE; y += PATCH_STRIDE) 
    {
        for (int x = 0; x < image.size().width - PATCH_SIZE; x += PATCH_STRIDE)
        {
            Mat patch(image, Rect(x, y, PATCH_SIZE, PATCH_SIZE));
            addHistogram(into, patch);
        }
    }
}

void Image::addHistogram(cv::Mat &into, const cv::Mat &patch) const
{
    cv::Mat p = cv::Mat::zeros(1, HSV_PATCH_LENGTH, CV_32F);

    typedef MatConstIterator_<Vec3b> iter;
    for (iter it = patch.begin<Vec3b>(); it != patch.end<Vec3b>(); it++)
    {
        rgb_color_t rgb = { (double)(*it)[2] / 255, (double)(*it)[1] / 255, (double)(*it)[0] / 255 };
        hsv_color_t hsv = rgb_to_hsv(rgb);

        int hbin = min((int)((hsv.hue / 360) * HSV_HISTOGRAM_BINS), HSV_HISTOGRAM_BINS - 1);
        int sbin = min((int)(hsv.sat * HSV_HISTOGRAM_BINS), HSV_HISTOGRAM_BINS - 1);
        int vbin = min((int)(hsv.val * HSV_HISTOGRAM_BINS), HSV_HISTOGRAM_BINS - 1);

        p.at<float>(hbin)                          = p.at<float>(hbin) + 1;
        p.at<float>(sbin +     HSV_HISTOGRAM_BINS) = p.at<float>(sbin + HSV_HISTOGRAM_BINS) + 1;
        p.at<float>(vbin + 2 * HSV_HISTOGRAM_BINS) = p.at<float>(vbin + 2 * HSV_HISTOGRAM_BINS) + 1;
    }

    into.push_back(p);
}

bool Image::loadVisualWords(cv::Mat &into, const cv::Mat &visualWords) const
{
    PATCHES_MATRIX(patches);
    loadPatches(patches);
    if (patches.size().height == 0) return false; // No patches for this image

    cv::Mat histogram = cv::Mat::zeros(1, visualWords.size().height, CV_32F);

    for (int patch = 0; patch < patches.size().height; patch++) 
    {
        int word = classifyPatch(patches.row(patch), visualWords);
        histogram.at<float>(word) = histogram.at<float>(word) + 1;
    }

    cv::Mat normalized;
    cv::normalize(histogram, normalized);
    into.push_back(normalized);
    return true;
}

int Image::classifyPatch(const cv::Mat &patch, const cv::Mat &visualWords) const
{
    double min_dist = cv::norm(patch, visualWords.row(0));
    int    min_ix   = 0;

    for (int word = 1; word < visualWords.size().height; word++)
    {
        double dist = cv::norm(patch, visualWords.row(word));
        if (dist < min_dist)
        {
            min_dist = dist;
            min_ix   = word;
        }
    }
    return min_ix;
}
