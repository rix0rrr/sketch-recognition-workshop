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

        if (++i == 3) break; // Early abort for debugging
    }

    return ret;
}
