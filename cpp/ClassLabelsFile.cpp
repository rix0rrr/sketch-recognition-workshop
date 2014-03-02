#include "ClassLabelsFile.h"
#include <fstream>

#define CLASSLABELS_FILENAME "classlabels.txt"

std::map<int, std::string> ClassLabelsFile::Load()
{
    std::map<int, std::string> list;
    std::ifstream classFile;
    classFile.open(CLASSLABELS_FILENAME);

    while (!classFile.eof())
    {
        int intLabel = -1;
        classFile >> intLabel;

        if (classFile.eof() || intLabel == -1)
        {
            break;
        }

        std::string label;
        classFile >> label;

        list[intLabel] = label;
    }

    classFile.close();
    return list;
}

void ClassLabelsFile::Save(std::map<int, std::string> classLabels)
{
    std::ofstream classFile;
    classFile.open(CLASSLABELS_FILENAME);
    for (std::map<int, std::string>::const_iterator it = classLabels.begin(); it != classLabels.end(); ++it)
    {
        classFile << it->first << " " << it->second << std::endl;
    }
    classFile.close();
}
