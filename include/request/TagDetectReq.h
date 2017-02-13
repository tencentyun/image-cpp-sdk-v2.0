#ifndef TAG_DETECT_REQ_H
#define TAG_DETECT_REQ_H
#include "ReqBase.h"
#include <stdint.h>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include "json/json.h"

namespace qcloud_image{

class TagDetectReq : public ReqBase
{
    public:
		TagDetectReq(const string& bucket)
			: ReqBase(bucket)
		{}


		bool SetUrl(const string& url) {
            _url = url;
            return true;
        }
		bool SetImage(const string& image) {
            _image = image;
            return true;
        }

		bool SetBuffer(const string& buffer) {
            _buffer = buffer;
            return true;
        }

		string url() { return _url; }
		string image() { return _image; }
		string buffer() { return _buffer; }

		virtual bool isParaValid(ImageResult& result){
			if (! ReqBase::isParaValid(result))
                return false;

			if (_url.empty() && _image.empty() && _buffer.empty()) {
				result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
				return false;
			} 

			if (!_image.empty()) {
				if (! FileUtil::isFileExists(_image)) {
					result.setCode(LOCAL_FILE_NOT_EXIST);

					string desc = LOCAL_FILE_NOT_EXIST_DESC;
					size_t pos = desc.find(SYMBOL_FILE);
					if (pos != string::npos)
					    desc.replace(pos, sizeof(SYMBOL_FILE)-1, _image);
					result.setMessage(desc);
					return false;
				}

				if (! FileUtil::getFileContent(_image).size()) {
	                result.setCode(INVALID_PARAM);
					result.setMessage(INVALID_PARAM_DESC);
	                return false;
            	}
			}
			
			return true;
		}

		string toJsonString() {
			Json::Value root;
			root["bucket"] = getBucket();
			if (!_url.empty()) {
				root["url"] = url();
			} else {
				root["image"] = image();
			}

			Json::FastWriter writer;
			return writer.write(root);
		}
	
	protected:
        TagDetectReq(){};

	protected: 				
		string				_url;
		string 				_image;
		string 				_buffer;
};

}

#endif
