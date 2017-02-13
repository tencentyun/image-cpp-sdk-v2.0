#include "util/FileUtil.h"
#include "util/CodecUtil.h"
#include "util/StringUtil.h"
#include "ImageSysConfig.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "ImageDefines.h"

using namespace std;
namespace qcloud_image {
    
string FileUtil::getFileContent(const string &localFilePath) 
{   
    std::ifstream fileInput(localFilePath.c_str(), std::ios::in | std::ios::binary);
    std::ostringstream out;

    out << fileInput.rdbuf();
    string content = out.str();

    fileInput.close();
    fileInput.clear();

    return content;
}

uint64_t FileUtil::getFileLen(const string &localFilePath)
{
    std::ifstream fileInput(localFilePath.c_str(), std::ios::in | std::ios::binary);
    fileInput.seekg(0, std::ios::end);
    uint64_t fileLen = fileInput.tellg();
    fileInput.close();
    return fileLen;
}

bool FileUtil::isFileExists(const string &filename)
{
    ifstream fin(filename.c_str() , std::ios::in);
    if (!fin)
    {
        return false;
    }
    fin.close();
    return true;
}

}
