#ifndef FILE_UTIL_H
#define FILE_UTIL_H
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <string>

using std::string;
namespace qcloud_image{

class FileUtil
{
    public:
    //获取文件内容
    static string getFileContent(const std::string& path);

    //返回文件大小
    static uint64_t getFileLen(const std::string& path);

    //判断文件是否存在
    static bool isFileExists(const std::string& path);
};

}

#endif
