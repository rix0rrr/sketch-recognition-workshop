#ifndef CLASSLABELS_FILE
#define CLASSLABELS_FILE

#include <map>
#include <string>

class ClassLabelsFile
{
public:
    static std::map<int, std::string> Load();
    static void Save(std::map<int, std::string> classLabels);
};

#endif
