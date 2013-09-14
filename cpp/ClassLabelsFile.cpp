#include "ClassLabelsFile.h"
#include <fstream>
#include <sstream>

#define CLASSLABELS_FILENAME "classlabels.txt"

std::map<int, std::string> ClassLabelsFile::Load()
{
    std::map<int, std::string> list;
    std::ifstream classFile;
    classFile.open(CLASSLABELS_FILENAME);


    std::string line;
    while (std::getline(classFile, line))
    {
        int space = line.find(" ");
        std::string label = line.substr(space + 1);

        std::istringstream iss(line.substr(0, space));
        int intLabel;
        iss >> intLabel;

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
