#ifndef OCR_REQ_H
#define OCR_REQ_H

#include "ReqBase.h"
#include <stdint.h>
#include <list>
#include <map>
#include <iostream>
#include <fstream>
#include "json/json.h"
#include "util/FileUtil.h"
#include "util/StringUtil.h"
#include <vector>


namespace qcloud_image{

class IdCardOcrReq : public ReqBase
{
    public:
        IdCardOcrReq(const string& bucket)
			: ReqBase(bucket)
		{}

		vector<string>& urls() { return _urls; }
		map<string, string>& images() { return _images; }
		map<string, string>& buffers() { return _buffers; }
		uint64_t card_type() {return _card_type;}
		
		uint64_t SetCardType(const uint64_t card_type) {
			_card_type = card_type;
		}
		bool AddUrl(const string& url) {
            _urls.push_back(url);
            return true;
        }
		bool AddImage(const string &name, const string& image) {
            _images[name] = image;
            return true;
        }
		bool AddBuffer(const string &name, const string& buffer) {
            _buffers[name] = buffer;
            return true;
        }
		
		virtual bool isParaValid(ImageResult& result){			
			if (_urls.empty() && _images.empty() && _buffers.empty()) {
				result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
				return false;
			}

			if((MAX_DETECTION_NUM < _urls.size()) || 
				(MAX_DETECTION_NUM < _images.size()) 
				|| (MAX_DETECTION_NUM < _buffers.size())) {
				result.setCode(IMAGE_EXCEED_LIMIT);
				result.setMessage(IMAGE_EXCEED_LIMIT_DESC);
				return false;
			}

			if (! _images.empty()) {
				for(map<string, string>::const_iterator it = _images.begin(); it != _images.end(); it++){
					if (! FileUtil::isFileExists(it->second)) {
						result.setCode(LOCAL_FILE_NOT_EXIST);

						string desc = LOCAL_FILE_NOT_EXIST_DESC;
						size_t pos = desc.find(SYMBOL_FILE);
						if (pos != string::npos)
						    desc.replace(pos, sizeof(SYMBOL_FILE)-1, it->second);
						result.setMessage(desc);
						return false;
					}

					if (! it->second.empty() && ! FileUtil::getFileContent(it->second).size()) {
		                result.setCode(INVALID_PARAM);
						result.setMessage(INVALID_PARAM_DESC);
		                return false;
            		}
				}

				
			}
			
			return true;
		}

		string toJsonString(){
			Json::Value root;
			root["bucket"] = getBucket();
			if (!_urls.empty()){
				for (size_t i = 0; i < _urls.size(); i++) {
					root["urls"].append(_urls[i]);
				}
			} else if (!_images.empty()){
				map<string, string>::iterator it;
				for (it = _images.begin(); it != _images.end(); it++) {
					root["images"].append(it->first);
				}
			}  else if (!_buffers.empty()) {
				map<string, string>::iterator it;
				for (it = _images.begin(); it != _images.end(); it++) {
					root["buffers"].append(it->first);
				}
			}

			Json::FastWriter writer;
			return writer.write(root);
		}
	

    protected:
        IdCardOcrReq() {}

	protected:
		uint64_t			_card_type;
		vector<string>		_urls;
		map<string, string>	_images;
		map<string, string>	_buffers;
};

class NameCardOcrReq : public ReqBase
{
    public:
        NameCardOcrReq(const string& bucket)
			: ReqBase(bucket)
		{}
		
		
		uint64_t ret_image() {return _ret_image;}
		vector<string>& urls() { return _urls; }
		map<string, string>& images() { return _images; }
		map<string, string>& buffers() { return _buffers; }

		uint64_t setRetImage(uint64_t ret_image) {
			_ret_image = ret_image;
		}
		bool AddUrl(const string& url) {
            _urls.push_back(url);
            return true;
        }
		bool AddImage(const string &name, const string& image) {
            _images[name] = image;
            return true;
        }
		bool AddBuffer(const string &name, const string& buffer) {
            _buffers[name] = buffer;
            return true;
        }
		
		virtual bool isParaValid(ImageResult& result){			
			if (_urls.empty() && _images.empty() && _buffers.empty()) {
				result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
				return false;
			}

			if((MAX_DETECTION_NUM < _urls.size()) || 
				(MAX_DETECTION_NUM < _images.size()) 
				|| (MAX_DETECTION_NUM < _buffers.size())) {
				result.setCode(IMAGE_EXCEED_LIMIT);
				result.setMessage(IMAGE_EXCEED_LIMIT_DESC);
				return false;
			}

			if (! _images.empty()) {
				for(map<string, string>::const_iterator it = _images.begin(); it != _images.end(); it++){
					if (! FileUtil::isFileExists(it->second)) {
						result.setCode(LOCAL_FILE_NOT_EXIST);

						string desc = LOCAL_FILE_NOT_EXIST_DESC;
						size_t pos = desc.find(SYMBOL_FILE);
						if (pos != string::npos)
						    desc.replace(pos, sizeof(SYMBOL_FILE)-1, it->second);
						result.setMessage(desc);
						return false;
					}

					if (! it->second.empty() && ! FileUtil::getFileContent(it->second).size()) {
		                result.setCode(INVALID_PARAM);
						result.setMessage(INVALID_PARAM_DESC);
		                return false;
            		}
				}
			}
			
			return true;
		}

		string toJsonString(){
			Json::Value root;
			root["bucket"] = getBucket();
			if (!_urls.empty()){
				for (size_t i = 0; i < _urls.size(); i++) {
					root["urls"].append(_urls[i]);
				}
			} else if (!_images.empty()){
				map<string, string>::iterator it;
				for (it = _images.begin(); it != _images.end(); it++) {
					root["images"].append(it->first);
				}
			}  else if (!_buffers.empty()) {
				map<string, string>::iterator it;
				for (it = _images.begin(); it != _images.end(); it++) {
					root["buffers"].append(it->first);
				}
			}

			Json::FastWriter writer;
			return writer.write(root);
		}

    protected:
        NameCardOcrReq() {}

	protected:
		uint64_t			_ret_image;
		vector<string>		_urls;
		map<string, string>	_images;
		map<string, string>	_buffers;
};

}
#endif // OCR_REQ_H
