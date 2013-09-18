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
            if (ret.size() >= MAX_CLASSES) break;
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
        if (basename(it->path()).at(0) == '.') continue;
        ret.include(*it);

        if (++i == MAX_IMAGES_PER_CLASS) break; // Early abort for debugging
    }

    return ret;
}

void pv(const ImageList &images) 
{
    cout << "[ ";
    for (ImageList::const_iterator i = images.begin(); i != images.end(); ++i)
    {
        std::cout << i->filename() << ' ';
    }
    cout << "]" << endl;
}
        

void partition(const ImageClassList &source, double fractionA, ImageClassList &targetA, ImageClassList &targetB)
{
    for (ImageClassList::const_iterator iter = source.begin(); iter != source.end(); iter++)
    {
        ImageClass copy(*iter);
        copy.shuffle();

        int fraction = static_cast<int>(copy.image_count() * fractionA);

        ImageClass A(copy);
        ImageClass B(copy);

        // Partition into
        // [...... A ........ | .... B ....]
        // 0              fraction       count
        B.remove(0, fraction);
        A.remove(fraction, A.image_count());

        targetA.push_back(A);
        targetB.push_back(B);
    }
}
