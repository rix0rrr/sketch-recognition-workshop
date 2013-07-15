#include <algorithm>
#include <iostream>

#include "Image.h"
#include "rgb_to_hsv.h"

using namespace cv;
using namespace std;

Image::Image(boost::filesystem::path filename) : m_filename(filename)
{
}

void Image::loadPatches(Mat &into)
{
    cout << m_filename.string() << endl;

    Mat image = imread(m_filename.string(), CV_LOAD_IMAGE_COLOR);
    if (image.data == NULL) return;

    for (int y = 0; y < image.size().height - PATCH_SIZE; y += PATCH_STRIDE) 
    {
        for (int x = 0; x < image.size().width - PATCH_SIZE; x += PATCH_STRIDE)
        {
            Mat patch(image, Rect(x, y, PATCH_SIZE, PATCH_SIZE));
            into.push_back(makeHistogram(patch));
        }
    }
}

Patch Image::makeHistogram(const cv::Mat &patch)
{
    Patch p;

    typedef MatConstIterator_<Vec3b> iter;
    for (iter it = patch.begin<Vec3b>(); it != patch.end<Vec3b>(); it++)
    {
        rgb_color_t rgb = { (double)(*it)[2] / 255, (double)(*it)[1] / 255, (double)(*it)[0] / 255 };
        hsv_color_t hsv = rgb_to_hsv(rgb);

        int hbin = min((int)((hsv.hue / 360) * HSV_HISTOGRAM_BINS), HSV_HISTOGRAM_BINS - 1);
        int sbin = min((int)(hsv.sat * HSV_HISTOGRAM_BINS), HSV_HISTOGRAM_BINS - 1);
        int vbin = min((int)(hsv.val * HSV_HISTOGRAM_BINS), HSV_HISTOGRAM_BINS - 1);

        p(hbin)                          = p(hbin) + 1;
        p(sbin +     HSV_HISTOGRAM_BINS) = p(sbin + HSV_HISTOGRAM_BINS) + 1;
        p(vbin + 2 * HSV_HISTOGRAM_BINS) = p(vbin + 2 * HSV_HISTOGRAM_BINS) + 1;
    }

    return p;
}
