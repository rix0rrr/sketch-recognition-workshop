#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <boost/filesystem.hpp>
#include <exception>
#include <iostream>
#include <algorithm>

#include <opencv2/ml/ml.hpp>

#include "Image.h"
#include "ClassLabelsFile.h"

using namespace std;
using namespace boost;
using namespace cv;

void loadClassifier(cv::Mat &words, CvSVM &svm)
{
    cv::FileStorage fs("learned-vocabulary.dat", FileStorage::READ);
    fs["vocabulary"] >> words;
    fs.release();

    svm.load("learned-svm.dat");
}

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        cerr << "Usage: recognizer IMAGE [IMAGE]" << endl;
        return 1;
    }

    try
    {
        std::map<int, std::string> classLabels = ClassLabelsFile::Load();

        cv::Mat words;
        CvSVM svm;
        loadClassifier(words, svm);

        for (int i = 1; i < argc; i++)
        {
            boost::filesystem::path filename(argv[i]);
            Image image(filename, true);

            cv::Mat imageWords(0, words.size().height, CV_32F);
            image.loadVisualWords(imageWords, words);

            float prediction = svm.predict(imageWords);
            int predictedClass = static_cast<int>(prediction);
            std::string classLabel = classLabels[predictedClass];

            if (argc == 2)
            {
                // One image, one output
                cout << classLabel << endl;
            } else
            {
                // Multiple files, list filenames and labels
                cout << argv[i] << " " << classLabel << endl;
            }
        }
        return 0;
    }
    catch (const std::exception &ex)
    {
        std::cerr << ex.what() << endl;
    }
}
