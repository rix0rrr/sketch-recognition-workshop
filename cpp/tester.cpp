#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <boost/filesystem.hpp>
#include <exception>
#include <iostream>
#include <algorithm>

#include <opencv2/ml/ml.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "ImageRepository.h"
#include "util.h"
#include "ClassLabelsFile.h"

using namespace std;
using namespace boost;
using namespace cv;

int main(void) {
    try
    {
        g_debugPatches = true;

        // Initialize random seed
        std::srand (unsigned ( std::time(0) ) );


        boost::filesystem::path filename("../images/guitar/7640.png");

        Image image(filename, false);
        PATCHES_MATRIX(patches);
        image.loadPatches(patches);

        return 0;
    }
    catch (const cv::Exception &ex)
    {
        std::cerr << ex.what() << endl;
    }
}

