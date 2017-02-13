#ifndef IMAGE_CONFIG_H
#define IMAGE_CONFIG_H
#include <string>
#include <stdint.h>

using std::string;
namespace qcloud_image{

class ImageConfig{
 
public:
    ImageConfig(){}
    ImageConfig(uint64_t appid,const std::string& secret_id,
                       const std::string& secret_key)
        : _appid(appid), _secret_id(secret_id), _secret_key(secret_key)
	{}

    ImageConfig(const ImageConfig& config) {
        _appid = config._appid;
        _secret_id = config._secret_id;
        _secret_key = config._secret_key;
    }

    uint64_t getAppid() const { return _appid; }
    string getSecretId() const { return _secret_id; };
    string getSecretKey() const { return _secret_key; };

private:
    uint64_t _appid;
    string _secret_id;
    string _secret_key;
};


}

#endif
