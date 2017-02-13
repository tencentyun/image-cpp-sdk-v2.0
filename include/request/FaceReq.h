#ifndef FACE_REQ_H
#define FACE_REQ_H

#include "ReqBase.h"
#include <stdint.h>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include "json/json.h"
#include "util/FileUtil.h"
#include "util/StringUtil.h"

namespace qcloud_image{

class FaceCompareReq : public ReqBase
{
    public:
		FaceCompareReq(const string& bucket)
			: ReqBase(bucket)
		{ }

		bool AddUrl(const string& url) {
            if (_urls.first.empty())
                _urls.first = url;
            else if (_urls.second.empty())
                _urls.second = url;
            else
                return false;
            return true;
        }
		bool AddImage(const string& image) {
            if (_images.first.empty())
                _images.first = image;
            else if (_images.second.empty())
                _images.second = image;
            else
                return false;
            return true;
        }
		bool AddBuffer(const string& buffer) {
            if (_buffers.first.empty())
                _buffers.first = buffer;
            else if (_buffers.second.empty())
                _buffers.second = buffer;
            else
                return false;
            return true;
        }
 
		virtual bool isParaValid(ImageResult& result){
            if (! ReqBase::isParaValid(result))
                return false;

			int size = 0;
            size += (_urls.first.empty()?0:1) + (_urls.second.empty()?0:1);
            size += (_images.first.empty()?0:1) + (_images.second.empty()?0:1);
            size += (_buffers.first.empty()?0:1) + (_buffers.second.empty()?0:1);

			if (2 > size) {
				result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
				return false;
			}

            if (! _images.first.empty() && ! FileUtil::isFileExists(_images.first)) {
                result.setCode(LOCAL_FILE_NOT_EXIST);

                string desc = LOCAL_FILE_NOT_EXIST_DESC;
                size_t pos = desc.find(SYMBOL_FILE);
                if (pos != string::npos)
                    desc.replace(pos, sizeof(SYMBOL_FILE)-1, _images.first);
                result.setMessage(desc);
                return false;
            }
            if (! _images.second.empty() && ! FileUtil::isFileExists(_images.second)) {
                result.setCode(LOCAL_FILE_NOT_EXIST);

                string desc = LOCAL_FILE_NOT_EXIST_DESC;
                size_t pos = desc.find(SYMBOL_FILE);
                if (pos != string::npos)
                    desc.replace(pos, sizeof(SYMBOL_FILE)-1, _images.second);
                result.setMessage(desc);
                return false;
            }

			if (! _images.second.empty() && ! FileUtil::getFileContent(_images.second).size()) {
                result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
                return false;
            }
			
			return true;
		}

        bool toJson(Json::Value& value) {
            if (_urls.first.empty() || _urls.second.empty())
                return false;

            value[PARA_URLA] = _urls.first;
            value[PARA_URLB] = _urls.second;
            return true;
        }

        bool toForm(HttpForm& form) {
            char count = 0;
            if (!_images.first.empty()) {
                form[PARA_IMAGEA] = std::make_pair(FileUtil::getFileContent(_images.first), true);
                ++ count;
            }
            if (!_images.second.empty()) {
                form[count?PARA_IMAGEB:PARA_IMAGEA] = std::make_pair(FileUtil::getFileContent(_images.second), true);
                ++ count;
            }
            if (count == 2) return true;
            if (!_buffers.first.empty()) {
                form[count?PARA_IMAGEB:PARA_IMAGEA] = std::make_pair(_buffers.first, true);
                ++ count;
            }
            if (count == 2) return true;
            if (!_buffers.second.empty()) {
                form[count?PARA_IMAGEB:PARA_IMAGEA] = std::make_pair(_buffers.second, true);
                ++ count;
            }
            if (count == 2) return true;
            if (!_urls.first.empty()) {
                form[count?PARA_URLB:PARA_URLA] = std::make_pair(_urls.first, false);
                ++ count;
            }
            if (count == 2) return true;
            if (!_urls.second.empty()) {
                form[count?PARA_URLB:PARA_URLA] = std::make_pair(_urls.second, false);
                ++ count;
            }
            if (count == 2) return true;
            return false;
        }

	protected:
        FaceCompareReq(){};

	protected:
        std::pair<string, string> _urls;
        std::pair<string, string> _images;
        std::pair<string, string> _buffers;
};

class FaceIdentifyReq : public ReqBase
{
    public:
		FaceIdentifyReq(const string& bucket)
			: ReqBase(bucket)
		{ }

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
		bool SetGroupId(const string& groupId) {
            _groupId = groupId;
            return true;
        }
 
		virtual bool isParaValid(ImageResult& result){
            if (! ReqBase::isParaValid(result))
                return false;

			if (_url.empty() && _image.empty() && _buffer.empty()) {
				result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
				return false;
			}

            if (! _image.empty() && ! FileUtil::isFileExists(_image)) {
                result.setCode(LOCAL_FILE_NOT_EXIST);

                string desc = LOCAL_FILE_NOT_EXIST_DESC;
                size_t pos = desc.find(SYMBOL_FILE);
                if (pos != string::npos)
                    desc.replace(pos, sizeof(SYMBOL_FILE)-1, _image);
                result.setMessage(desc);
                return false;
            }

			if (! _image.empty() && ! FileUtil::getFileContent(_image).size()) {
                result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
                return false;
            }
			
			return true;
		}

        bool toJson(Json::Value& value) {
            if (_url.empty())
                return false;

            value[PARA_URL] = _url;
			value[PARA_GROUP_ID] = _groupId;
            return true;
        }

        bool toForm(HttpForm& form) {
			if (_image.empty() && _buffer.empty())
				return false;
			
            if (!_image.empty()) {
                form[PARA_IMAGE] = std::make_pair(FileUtil::getFileContent(_image), true);
            } else {
                form[PARA_IMAGE] = std::make_pair(_buffer, true);
            }
			form[PARA_GROUP_ID] = std::make_pair(_groupId, false);
            return true;
        }

	protected:
        FaceIdentifyReq(){};

	protected:
		std::string _groupId;
        std::string _url;
        std::string _image;
        std::string _buffer;
};

class FaceIdCardCompareReq : public ReqBase
{
    public:
		FaceIdCardCompareReq(const string& bucket)
			: ReqBase(bucket)
		{ }

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
		bool SetIdCardNumber(const string& number) {
            _idCardNumber = number;
            return true;
        }
		bool SetIdCardName(const string& name) {
            _idCardName = name;
            return true;
        }
		bool SetSessionId(const string& session) {
            _sessionId = session;
            return true;
        }
 
		virtual bool isParaValid(ImageResult& result){
            if (! ReqBase::isParaValid(result))
                return false;

			if (_url.empty() && _image.empty() && _buffer.empty()) {
				result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
				return false;
			}

            if (_idCardNumber.empty() || _idCardName.empty()) {
				result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
				return false;
			}

            if (! _image.empty() && ! FileUtil::isFileExists(_image)) {
                result.setCode(LOCAL_FILE_NOT_EXIST);

                string desc = LOCAL_FILE_NOT_EXIST_DESC;
                size_t pos = desc.find(SYMBOL_FILE);
                if (pos != string::npos)
                    desc.replace(pos, sizeof(SYMBOL_FILE)-1, _image);
                result.setMessage(desc);
                return false;
            }

			if (! _image.empty() && ! FileUtil::getFileContent(_image).size()) {
                result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
                return false;
            }
			return true;
		}

        bool toJson(Json::Value& value) {
            if (_url.empty())
                return false;

            value[PARA_URL] = _url;
			value[PARA_IDCARD_NUMBER] = _idCardNumber;
			value[PARA_IDCARD_NAME] = _idCardName;

            if (! _sessionId.empty())
                value[PARA_SESSION_ID] = _sessionId;
            return true;
        }

        bool toForm(HttpForm& form) {
			if (_image.empty() && _buffer.empty())
				return false;
			
            if (! _image.empty()) {
                form[PARA_IMAGE] = std::make_pair(FileUtil::getFileContent(_image), true);
            } else {
                form[PARA_IMAGE] = std::make_pair(_buffer, true);
            }
			form[PARA_IDCARD_NUMBER] = std::make_pair(_idCardNumber, false);
			form[PARA_IDCARD_NAME] = std::make_pair(_idCardName, false);

            if (! _sessionId.empty())
                form[PARA_SESSION_ID] = std::make_pair(_sessionId, false);
            return true;
        }

	protected:
        FaceIdCardCompareReq(){};

	protected:
		std::string _idCardNumber;
		std::string _idCardName;
        std::string _url;
        std::string _image;
        std::string _buffer;
        std::string _sessionId;
};

class FaceLiveGetFourReq : public ReqBase
{
    public:
		FaceLiveGetFourReq(const string& bucket)
			: ReqBase(bucket)
		{ }

		bool SetSeq(const string& seq) {
            _seq = seq;
            return true;
        }
 
		virtual bool isParaValid(ImageResult& result){
            if (! ReqBase::isParaValid(result))
                return false;

			return true;
		}

        bool toJson(Json::Value& value) {
            if (! _seq.empty())
                value[PARA_SEQ] = _seq;
            return true;
        }

        bool toForm(HttpForm& form) {
            return false;
        }

	protected:
        FaceLiveGetFourReq(){};

	protected:
        std::string _seq;
};

class FaceLiveDetectFourReq : public ReqBase
{
    public:
		FaceLiveDetectFourReq(const string& bucket)
			: ReqBase(bucket), _compareFlag(false)
		{ }

		bool SetValidateData(const string& data) {
            _validateData = data;
            return true;
        }
		bool SetVideo(const string& video) {
            _video = video;
            return true;
        }
		bool SetVideoBuffer(const string& buffer) {
            _videoBuffer = buffer;
            return true;
        }
		bool SetCard(const string& card) {
            _compareFlag = true;
            _card = card;
            return true;
        }
		bool SetCardBuffer(const string& buffer) {
            _compareFlag = true;
            _cardBuffer = buffer;
            return true;
        }
		bool SetSeq(const string& seq) {
            _seq = seq;
            return true;
        }
 
		virtual bool isParaValid(ImageResult& result){
            if (! ReqBase::isParaValid(result))
                return false;

			if (_videoBuffer.empty() && _video.empty()) {
				result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
				return false;
			}

            if (_validateData.empty()) {
				result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
				return false;
			}

            if (! _video.empty() && ! FileUtil::isFileExists(_video)) {
                result.setCode(LOCAL_FILE_NOT_EXIST);

                string desc = LOCAL_FILE_NOT_EXIST_DESC;
                size_t pos = desc.find(SYMBOL_FILE);
                if (pos != string::npos)
                    desc.replace(pos, sizeof(SYMBOL_FILE)-1, _video);
                result.setMessage(desc);
                return false;
            }

			if (! _video.empty() && ! FileUtil::getFileContent(_video).size()) {
                result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
                return false;
            }
			
            if (! _card.empty() && ! FileUtil::isFileExists(_card)) {
                result.setCode(LOCAL_FILE_NOT_EXIST);

                string desc = LOCAL_FILE_NOT_EXIST_DESC;
                size_t pos = desc.find(SYMBOL_FILE);
                if (pos != string::npos)
                    desc.replace(pos, sizeof(SYMBOL_FILE)-1, _card);
                result.setMessage(desc);
                return false;
            }

			if (! _card.empty() && ! FileUtil::getFileContent(_card).size()) {
                result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
                return false;
            }
			
			return true;
		}

        bool toJson(Json::Value& value) {
            return false;
        }

        bool toForm(HttpForm& form) {
			form[PARA_VALIDATE_DATA] = std::make_pair(_validateData, false);
            if (! _video.empty()) {
                form[PARA_VIDEO] = std::make_pair(FileUtil::getFileContent(_video), true);
            } else {
                form[PARA_VIDEO] = std::make_pair(_videoBuffer, true);
            }
			form[PARA_COMPARE_FLAG] = std::make_pair(_compareFlag?"true":"false", false);
            if (_compareFlag) {
                if (! _card.empty()) {
                    form[PARA_CARD] = std::make_pair(FileUtil::getFileContent(_card), true);
                } else {
                    form[PARA_CARD] = std::make_pair(_cardBuffer, true);
                }
            }

            if (! _seq.empty())
                form[PARA_SEQ] = std::make_pair(_seq, false);
            return true;
        }

	protected:
        FaceLiveDetectFourReq(){};

	protected:
		bool _compareFlag;
		std::string _validateData;
        std::string _video;
		std::string _videoBuffer;
        std::string _card;
        std::string _cardBuffer;
        std::string _seq;
};

class FaceIdCardLiveDetectFourReq : public ReqBase
{
    public:
		FaceIdCardLiveDetectFourReq(const string& bucket)
			: ReqBase(bucket)
		{ }

		bool SetValidateData(const string& data) {
            _validateData = data;
            return true;
        }
		bool SetVideo(const string& video) {
            _video = video;
            return true;
        }
		bool SetVideoBuffer(const string& buffer) {
            _videoBuffer = buffer;
            return true;
        }
		bool SetIdCardNumber(const string& number) {
            _idCardNumber = number;
            return true;
        }
		bool SetIdCardName(const string& name) {
            _idCardName = name;
            return true;
        }
		bool SetSeq(const string& seq) {
            _seq = seq;
            return true;
        }
 
		virtual bool isParaValid(ImageResult& result){
            if (! ReqBase::isParaValid(result))
                return false;

			if (_videoBuffer.empty() && _video.empty()) {
				result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
				return false;
			}

            if (_validateData.empty() || _idCardNumber.empty() || _idCardName.empty()) {
				result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
				return false;
			}

            if (! _video.empty() && ! FileUtil::isFileExists(_video)) {
                result.setCode(LOCAL_FILE_NOT_EXIST);

                string desc = LOCAL_FILE_NOT_EXIST_DESC;
                size_t pos = desc.find(SYMBOL_FILE);
                if (pos != string::npos)
                    desc.replace(pos, sizeof(SYMBOL_FILE)-1, _video);
                result.setMessage(desc);
                return false;
            }

			if (! _video.empty() && ! FileUtil::getFileContent(_video).size()) {
                result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
                return false;
            }
			
			return true;
		}

        bool toJson(Json::Value& value) {
            return false;
        }

        bool toForm(HttpForm& form) {
			form[PARA_VALIDATE_DATA] = std::make_pair(_validateData, false);
            if (! _video.empty()) {
                form[PARA_VIDEO] = std::make_pair(FileUtil::getFileContent(_video), true);
            } else {
                form[PARA_VIDEO] = std::make_pair(_videoBuffer, true);
            }
			form[PARA_IDCARD_NUMBER] = std::make_pair(_idCardNumber, false);
			form[PARA_IDCARD_NAME] = std::make_pair(_idCardName, false);
            if (! _seq.empty())
                form[PARA_SEQ] = std::make_pair(_seq, false);
            return true;
        }

	protected:
        FaceIdCardLiveDetectFourReq(){};

	protected:
		std::string _validateData;
        std::string _video;
		std::string _videoBuffer;
        std::string _idCardNumber;
        std::string _idCardName;
        std::string _seq;
};

class FaceVerifyReq : public ReqBase
{
    public:
		FaceVerifyReq(const string& bucket)
			: ReqBase(bucket)
		{ }

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
		bool SetPersonId(const string& personId) {
            _personId = personId;
            return true;
        }
 
		virtual bool isParaValid(ImageResult& result){
            if (! ReqBase::isParaValid(result))
                return false;

			if (_url.empty() && _image.empty() && _buffer.empty()) {
				result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
				return false;
			}

            if (! _image.empty() && ! FileUtil::isFileExists(_image)) {
                result.setCode(LOCAL_FILE_NOT_EXIST);

                string desc = LOCAL_FILE_NOT_EXIST_DESC;
                size_t pos = desc.find(SYMBOL_FILE);
                if (pos != string::npos)
                    desc.replace(pos, sizeof(SYMBOL_FILE)-1, _image);
                result.setMessage(desc);
                return false;
            }

			if (! _image.empty() && ! FileUtil::getFileContent(_image).size()) {
                result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
                return false;
            }
			return true;
		}

        bool toJson(Json::Value& value) {
            if (_url.empty())
                return false;

            value[PARA_URL] = _url;
			value[PARA_PERSON_ID] = _personId;
            return true;
        }

        bool toForm(HttpForm& form) {
			if (_image.empty() && _buffer.empty())
				return false;
			
            if (!_image.empty()) {
                form[PARA_IMAGE] = std::make_pair(FileUtil::getFileContent(_image), true);
            } else {
                form[PARA_IMAGE] = std::make_pair(_buffer, true);
            }
			form[PARA_PERSON_ID] = std::make_pair(_personId, false);
            return true;
        }

	protected:
        FaceVerifyReq(){};

	protected:
		std::string _personId;
        std::string _url;
        std::string _image;
        std::string _buffer;
};

class FaceDetectReq : public ReqBase
{
    public:
		FaceDetectReq(const string& bucket)
			: ReqBase(bucket), _mode(0)
		{ }

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
		bool SetMode(int mode) {
            _mode = mode;
            return true;
        }
 
		virtual bool isParaValid(ImageResult& result){
            if (! ReqBase::isParaValid(result))
                return false;

			if (_url.empty() && _image.empty() && _buffer.empty()) {
				result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
				return false;
			}
            if (_mode != 0 && _mode != 1) {
				result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
            }

            if (! _image.empty() && ! FileUtil::isFileExists(_image)) {
                result.setCode(LOCAL_FILE_NOT_EXIST);

                string desc = LOCAL_FILE_NOT_EXIST_DESC;
                size_t pos = desc.find(SYMBOL_FILE);
                if (pos != string::npos)
                    desc.replace(pos, sizeof(SYMBOL_FILE)-1, _image);
                result.setMessage(desc);
                return false;
            }

			if (! _image.empty() && ! FileUtil::getFileContent(_image).size()) {
                result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
                return false;
            }
			
			return true;
		}

        bool toJson(Json::Value& value) {
            if (_url.empty())
                return false;

            value[PARA_URL] = _url;
			value[PARA_MODE] = _mode;
            return true;
        }

        bool toForm(HttpForm& form) {
			if (_image.empty() && _buffer.empty())
				return false;
			
            if (!_image.empty()) {
                form[PARA_IMAGE] = std::make_pair(FileUtil::getFileContent(_image), true);
            } else {
                form[PARA_IMAGE] = std::make_pair(_buffer, true);
            }
			form[PARA_MODE] = std::make_pair(StringUtil::IntToString(_mode), false);
            return true;
        }

	protected:
        FaceDetectReq(){};

	protected:
		int _mode;
        std::string _url;
        std::string _image;
        std::string _buffer;
};

class FaceShapeReq : public ReqBase
{
    public:
		FaceShapeReq(const string& bucket)
			: ReqBase(bucket), _mode(0)
		{ }

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
		bool SetMode(int mode) {
            _mode = mode;
            return true;
        }
 
		virtual bool isParaValid(ImageResult& result){
            if (! ReqBase::isParaValid(result))
                return false;

			if (_url.empty() && _image.empty() && _buffer.empty()) {
				result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
				return false;
			}
            if (_mode != 0 && _mode != 1) {
				result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
            }

            if (! _image.empty() && ! FileUtil::isFileExists(_image)) {
                result.setCode(LOCAL_FILE_NOT_EXIST);

                string desc = LOCAL_FILE_NOT_EXIST_DESC;
                size_t pos = desc.find(SYMBOL_FILE);
                if (pos != string::npos)
                    desc.replace(pos, sizeof(SYMBOL_FILE)-1, _image);
                result.setMessage(desc);
                return false;
            }
			
			if (! _image.empty() && ! FileUtil::getFileContent(_image).size()) {
                result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
				return false;
            }
			
			return true;
		}

        bool toJson(Json::Value& value) {
            if (_url.empty())
                return false;

            value[PARA_URL] = _url;
			value[PARA_MODE] = _mode;
            return true;
        }

        bool toForm(HttpForm& form) {
			if (_image.empty() && _buffer.empty())
				return false;
			
            if (!_image.empty()) {
                form[PARA_IMAGE] = std::make_pair(FileUtil::getFileContent(_image), true);
            } else {
                form[PARA_IMAGE] = std::make_pair(_buffer, true);
            }
			form[PARA_MODE] = std::make_pair(StringUtil::IntToString(_mode), false);
            return true;
        }

	protected:
        FaceShapeReq(){};

	protected:
		int _mode;
        std::string _url;
        std::string _image;
        std::string _buffer;
};
}

#endif // FACE_REQ_H
