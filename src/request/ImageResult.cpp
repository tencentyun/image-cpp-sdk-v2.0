#include "request/ImageResult.h"
#include "json/json.h"

namespace qcloud_image{

ImageResult::ImageResult()
{}

ImageResult::ImageResult(int code, string message)
{
    this->code = code;
    this->message = message;
}

ImageResult::~ImageResult()
{}

void ImageResult::setCode(int code)
{
    this->code = code;
}
void ImageResult::setMessage(string message)
{
    this->message = message;
}

string ImageResult::toJsonString()
{
    Json::Value root;
    root["code"] = this->code;
    root["message"] = this->message;

    Json::FastWriter fast_writer;
    return fast_writer.write(root);
}

}
