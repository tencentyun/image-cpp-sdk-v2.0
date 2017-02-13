#ifndef REQ_BASE_H
#define REQ_BASE_H
#include "ImageResult.h"
#include "ImageDefines.h"
#include "ImageParams.h"
#include <iostream>
#include <string>

using namespace std;

namespace qcloud_image{

class ReqBase
{
public:
    ReqBase()
		: _bucket("")
	{};
    ReqBase(const string& bucket) 
		: _bucket(bucket)
	{}

	virtual bool isParaValid(ImageResult& result) { return true; }
    string getBucket() { return _bucket; }

protected:
    string	_bucket;
};

}
#endif
