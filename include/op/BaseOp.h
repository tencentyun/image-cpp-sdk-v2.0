#ifndef BASE_OP_H
#define BASE_OP_H

#include "ImageConfig.h"
#include "ImageDefines.h"
#include <string>
#include <stdint.h>

using namespace std;

namespace qcloud_image{

class BaseOp
{
    public:
        BaseOp(ImageConfig& imageConfig)
		   	: _config(imageConfig)
		{};

        ImageConfig& getImageConfig() { return _config; }
        uint64_t getAppid() { return _config.getAppid(); }
        string getSecretID() { return _config.getSecretId(); }       
        string getSecretKey() { return _config.getSecretKey(); };

    protected:
        BaseOp(){};

        ImageConfig _config;
        string op;
};

}
#endif
