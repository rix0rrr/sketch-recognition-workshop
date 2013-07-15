#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <boost/filesystem.hpp>
#include <exception>
#include <iostream>
#include <algorithm>

#include "ImageRepository.h"

using namespace std;
using namespace boost;
using namespace cv;

int main(void) {
    try
    {
        // Load all patches of all classes
        ImageRepository images("../images/jpg");
        ImageClassList classes = images.classes();

        Mat patches(0, HSV_PATCH_LENGTH, CV_32F);
        for (ImageClassList::iterator it = classes.begin(); it != classes.end(); it++)
        {
            it->loadPatches(patches);
        }

        // K-means
        cout << "Clustering..." << endl;
        int K = min(patches.size().height, VISUAL_WORD_COUNT);

        Mat labels;
        Mat centers;
        kmeans(patches, K, labels, TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 10000, 0.0001),
                5, // attempts
                KMEANS_PP_CENTERS, centers);

        cout << centers << endl;

        return 0;
    }
    catch (const std::exception &ex)
    {
        std::cerr << ex.what() << endl;
    }
}
