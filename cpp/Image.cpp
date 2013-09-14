#include <algorithm>
#include <iostream>
#include <limits>
#include <cassert>
#include <cmath>

#include "util.h"
#include "Image.h"
#include "rgb_to_hsv.h"
#include "hogdescriptor_visu.h"

using namespace cv;
using namespace std;

bool g_debugPatches = false;

Image::Image(boost::filesystem::path filename, bool silent) : m_filename(filename), m_silent(silent)
{
}

Rect imageBoundingBox(const Mat &image) 
{
    int x0 = image.size().width, y0 = image.size().height, x1 = 0, y1 = 0;

    for (int y = 0; y < image.size().height; y++)
    {
        for (int x = 0; x < image.size().width; x++)
        {
            if (image.at<uchar>(y, x) < 50) // Black (ish)
            {
                if (x < x0) x0 = x;
                if (x > x1) x1 = x;
                if (y < y0) y0 = y;
                if (y > y1) y1 = y;
            }
        }
    }

    return Rect(x0, y0, x1 - x0 + 1, y1 - y0 + 1);
}

void Image::loadPatches(Mat &into) const
{
    if (!m_silent) cout << m_filename.string() << endl;

    Mat anySize = imread(m_filename.string().c_str(), CV_LOAD_IMAGE_GRAYSCALE);
    if (anySize.data == NULL) {
        cout << "Failed" << endl;
        return;
    }

    // Find bounding box of image and rescale

    Mat image;
    resize(Mat(anySize, imageBoundingBox(anySize)), image, Size(IMAGE_SIZE, IMAGE_SIZE), 0, 0, INTER_LINEAR);

    for (int y = 0; y < image.size().height - PATCH_SIZE + 1; y += PATCH_STRIDE) 
    {
        for (int x = 0; x < image.size().width - PATCH_SIZE + 1; x += PATCH_STRIDE)
        {
            addHistogram(into, image, x, y);
        }
    }
}

void Image::addHistogram(cv::Mat &into, const cv::Mat &image, int patch_x, int patch_y) const
{
    // Patches are 32x32 pixels, will be divided into 4x4 cells, out of which
    // a histogram of gradients will be made.
    cv::Mat p = cv::Mat::zeros(1, PATCH_CELLS * PATCH_CELLS * GRADIENT_BINS, CV_32F);

    for (int j = 0; j < PATCH_CELLS; j++)
    {
        for (int i = 0; i < PATCH_CELLS; i++)
        {
            int x = patch_x + i * CELL_SIZE;
            int y = patch_y + j * CELL_SIZE;

            addCellHoG(p, (j * PATCH_CELLS + i) * GRADIENT_BINS, image, x, y);
        }
    }

    cv::Mat normalized;
    cv::normalize(p, normalized);
    into.push_back(normalized);

    if (g_debugPatches) {
        Mat visualizedWords = get_hogdescriptor_visu(image, normalized, patch_x, patch_y);
        imshow("Bla", visualizedWords);
        waitKey();
    }

    into.push_back(normalized);
}

void Image::addCellHoG(cv::Mat &into, int matIndex, const cv::Mat &image, int cell_x, int cell_y) const
{
    Mat cell(image, Rect(cell_x, cell_y, CELL_SIZE, CELL_SIZE));

    for (int y = 0; y < CELL_SIZE; y++)
    {
        for (int x = 0; x < CELL_SIZE; x++)
        {
            if ((cell_x + x) <= 0 || (cell_y + y) <= 0 || (cell_x + x) >= image.size().width - 1 || (cell_y + y) >= image.size().height - 1) continue;

//            cout << x << " " << y << image.at<uchar>(x, y) << endl;

            double dIdx = cell.at<uchar>(y, x + 1) - cell.at<uchar>(y, x - 1);
            double dIdy = cell.at<uchar>(y + 1, x) - cell.at<uchar>(y - 1, x);

            if (dIdx != 0 || dIdy != 0) {
                double theta = dIdx != 0 ? atan(dIdy / dIdx) : 0.5 * M_PI;

                // Map from [-1/2PI .. 1/2PI] to [0..4]
                double bin = (theta + 0.5 * M_PI) / GRADIENT_BIN_WIDTH;
                // We want the center of a bin to correspond to a complete increase of that bin
                // otherwise, fractionally between bins
                double left_bin = GRADIENT_BINS + bin - 0.5; // Make sure to remain positive

                double left_fraction = 1 - (left_bin - (int)left_bin); // Closer is better

                into.at<float>(matIndex + (int)left_bin % GRADIENT_BINS)       += left_fraction;
                into.at<float>(matIndex + (int)(left_bin + 1) % GRADIENT_BINS) += 1 - left_fraction;
            }
        }
    }
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
