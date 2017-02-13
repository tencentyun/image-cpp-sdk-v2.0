#ifndef IMAGE_RESULT_H
#define IMAGE_RESULT_H
#include <string>

using std::string;
namespace qcloud_image{

class ImageResult
{
public:
    ImageResult();
    ImageResult(int code, string message);
    ~ImageResult();
    void setCode(int code);
    void setMessage(string message);
    string toJsonString();
private:
    int code;
    string message;
};

}


#endif
