#include <algorithm>
#include <iostream>

#include "ImageRepository.h"

using namespace boost;
using namespace boost::filesystem;
using namespace cv;
using namespace std;

ImageRepository::ImageRepository(string directory) : m_directory(directory)
{
}

std::vector<ImageClass> ImageRepository::classes()
{
    vector<ImageClass> ret;

    path p(m_directory);
    for (directory_iterator it = directory_iterator(p); it != directory_iterator(); it++)
    {
        if (is_directory(*it))
        {
            ret.push_back(makeClass(*it));
        }
    }

    return ret;
}

ImageClass ImageRepository::makeClass(boost::filesystem::path directory)
{
    ImageClass ret(directory.filename().string());

    int i = 0;
    for (directory_iterator it = directory_iterator(directory); it != directory_iterator(); it++)
    {
        ret.include(*it);

        if (++i == MAX_IMAGES_PER_CLASS) break; // Early abort for debugging
    }

    return ret;
}

void partition(const ImageClassList &source, float fractionA, ImageClassList &targetA, ImageClassList &targetB)
{
    for (ImageClassList::const_iterator iter = source.begin(); iter != source.end(); iter++)
    {
        ImageClass copy(*iter);
        copy.shuffle();

        int fraction = copy.image_count() * fractionA;

        ImageClass A(copy);
        ImageClass B(copy);

        A.remove(fraction, A.image_count());
        B.remove(0, fraction);

        targetA.push_back(A);
        targetB.push_back(B);
    }
}
