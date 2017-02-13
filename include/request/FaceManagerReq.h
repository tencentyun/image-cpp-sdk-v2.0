#ifndef FACE_MANAGER_REQ_H
#define FACE_MANAGER_REQ_H

#include "ReqBase.h"
#include <stdint.h>
#include <list>
#include <map>
#include <iostream>
#include <fstream>
#include "json/json.h"
#include "util/FileUtil.h"
#include "util/StringUtil.h"

namespace qcloud_image{

class FaceNewPersonReq : public ReqBase
{
    public:
		FaceNewPersonReq(const string& bucket)
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
		bool AddGroupId(const string& groupId) {
            _groupIds.push_back(groupId);
            return true;
        }
		bool SetPersonId(const string& personId) {
            _personId = personId;
            return true;
        }
		bool SetPersonName(const string& personName) {
            _personName = personName;
            return true;
        }
		bool SetTag(const string& tag) {
            _tag = tag;
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

            if (_groupIds.empty() || _personId.empty()) {
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

            value[PARA_GROUP_IDS] = Json::Value(Json::arrayValue);
            std::list<std::string>::iterator iter = _groupIds.begin();
            for (; iter != _groupIds.end(); ++iter) {
                value[PARA_GROUP_IDS].append(*iter);
            }
            value[PARA_URL] = _url;
			value[PARA_PERSON_ID] = _personId;
            if (! _personName.empty())
                value[PARA_PERSON_NAME] = _personName;
            if (! _tag.empty())
                value[PARA_TAG] = _tag;
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

            int index = 0;
            std::list<std::string>::iterator iter = _groupIds.begin();
            for (; iter != _groupIds.end(); ++iter) {
                form[PARA_GROUP_IDS+"["+StringUtil::IntToString(index++)+"]"] = std::make_pair(*iter, false);
            }
			form[PARA_PERSON_ID] = std::make_pair(_personId, false);

            if (! _personName.empty())
                form[PARA_PERSON_NAME] = std::make_pair(_personName, false);
            if (! _tag.empty())
                form[PARA_TAG] = std::make_pair(_tag, false);
            return true;
        }

	protected:
        FaceNewPersonReq(){};

	protected:
        std::list<std::string> _groupIds;
        std::string _personId;
        std::string _url;
        std::string _image;
        std::string _buffer;
        std::string _personName;
        std::string _tag;
};

class FaceDelPersonReq : public ReqBase
{
    public:
		FaceDelPersonReq(const string& bucket)
			: ReqBase(bucket)
		{ }

		bool SetPersonId(const string& personId) {
            _personId = personId;
            return true;
        }
 
		virtual bool isParaValid(ImageResult& result){
            if (! ReqBase::isParaValid(result))
                return false;

            if (_personId.empty()) {
				result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
				return false;
            }

			return true;
		}

        bool toJson(Json::Value& value) {
			value[PARA_PERSON_ID] = _personId;
            return true;
        }

        bool toForm(HttpForm& form) {
            return false;
        }

	protected:
        FaceDelPersonReq(){};

	protected:
        std::string _personId;
};

class FaceAddFaceReq : public ReqBase
{
    public:
		FaceAddFaceReq(const string& bucket)
			: ReqBase(bucket)
		{ }

		bool AddUrl(const string& url) {
            _urls.push_back(url);
            return true;
        }
		bool AddImage(const string& image) {
            _images.push_back(image);
            return true;
        }
		bool AddBuffer(const string& buffer) {
            _buffers.push_back(buffer);
            return true;
        }
		bool SetPersonId(const string& personId) {
            _personId = personId;
            return true;
        }
		bool SetTag(const string& tag) {
            _tag = tag;
            return true;
        }
 
		virtual bool isParaValid(ImageResult& result){
            if (! ReqBase::isParaValid(result))
                return false;

			if (_urls.empty() && _images.empty() && _buffers.empty()) {
				result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
				return false;
			}

            if (_personId.empty()) {
				result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
				return false;
            }

            if (! _images.empty()) {
                std::list<std::string>::iterator iter = _images.begin();
                for (; iter != _images.end(); ++iter) {
                    if (! FileUtil::isFileExists(*iter)) {
                        result.setCode(LOCAL_FILE_NOT_EXIST);

                        string desc = LOCAL_FILE_NOT_EXIST_DESC;
                        size_t pos = desc.find(SYMBOL_FILE);
                        if (pos != string::npos)
                            desc.replace(pos, sizeof(SYMBOL_FILE)-1, *iter);
                        result.setMessage(desc);
                        return false;
                    }

					if (! FileUtil::getFileContent(*iter).size()) {
		                result.setCode(INVALID_PARAM);
						result.setMessage(INVALID_PARAM_DESC);
						return false;
            		}
                }
            }
			return true;
		}

        bool toJson(Json::Value& value) {
            if (_urls.empty())
                return false;

			value[PARA_PERSON_ID] = _personId;
            value[PARA_URLS] = Json::Value(Json::arrayValue);
            std::list<std::string>::iterator iter = _urls.begin();
            for (; iter != _urls.end(); ++iter) {
                value[PARA_URLS].append(*iter);
            }
            if (! _tag.empty())
                value[PARA_TAG] = _tag;
            return true;
        }

        bool toForm(HttpForm& form) {
			if (_images.empty() && _buffers.empty())
				return false;
			
			form[PARA_PERSON_ID] = std::make_pair(_personId, false);
            int index = 0;
            std::list<std::string>::iterator iter = _images.begin();
            for (; iter != _images.end(); ++iter) {
                form[PARA_IMAGES+"["+StringUtil::IntToString(index++)+"]"]
                    = std::make_pair(FileUtil::getFileContent(*iter), true);
            }
            for (iter = _buffers.begin(); iter != _buffers.end(); ++iter) {
                form[PARA_IMAGES+"["+StringUtil::IntToString(index++)+"]"] = std::make_pair(*iter, true);
            }
            if (! _tag.empty())
                form[PARA_TAG] = std::make_pair(_tag, false);
            return true;
        }

	protected:
        FaceAddFaceReq(){};

	protected:
        std::list<std::string> _urls;
        std::list<std::string> _images;
        std::list<std::string> _buffers;
        std::string _personId;
        std::string _tag;
};

class FaceDelFaceReq : public ReqBase
{
    public:
		FaceDelFaceReq(const string& bucket)
			: ReqBase(bucket)
		{ }

		bool AddFaceId(const string& faceId) {
            _faceIds.push_back(faceId);
            return true;
        }
		bool SetPersonId(const string& personId) {
            _personId = personId;
            return true;
        }
 
		virtual bool isParaValid(ImageResult& result){
            if (! ReqBase::isParaValid(result))
                return false;

            if (_personId.empty() || _faceIds.empty()) {
				result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
				return false;
            }
			return true;
		}

        bool toJson(Json::Value& value) {
			value[PARA_PERSON_ID] = _personId;
            value[PARA_FACE_IDS] = Json::Value(Json::arrayValue);
            std::list<std::string>::iterator iter = _faceIds.begin();
            for (; iter != _faceIds.end(); ++iter) {
                value[PARA_FACE_IDS].append(*iter);
            }
            return true;
        }

        bool toForm(HttpForm& form) {
            return false;
        }

	protected:
        FaceDelFaceReq(){};

	protected:
        std::list<std::string> _faceIds;
        std::string _personId;
};

class FaceSetInfoReq : public ReqBase
{
    public:
		FaceSetInfoReq(const string& bucket)
			: ReqBase(bucket)
		{ }

		bool SetPersonId(const string& personId) {
            _personId = personId;
            return true;
        }
		bool SetPersonName(const string& personName) {
            _personName = personName;
            return true;
        }
		bool SetTag(const string& tag) {
            _tag = tag;
            return true;
        }
 
		virtual bool isParaValid(ImageResult& result){
            if (! ReqBase::isParaValid(result))
                return false;

            if (_personId.empty()) {
				result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
				return false;
            }
			return true;
		}

        bool toJson(Json::Value& value) {
			value[PARA_PERSON_ID] = _personId;
            if (! _personName.empty())
                value[PARA_PERSON_NAME] = _personName;
            if (! _tag.empty())
                value[PARA_TAG] = _tag;
            return true;
        }

        bool toForm(HttpForm& form) {
            return false;
        }

	protected:
        FaceSetInfoReq(){};

	protected:
        std::string _personId;
        std::string _personName;
        std::string _tag;
};

class FaceGetInfoReq : public ReqBase
{
    public:
		FaceGetInfoReq(const string& bucket)
			: ReqBase(bucket)
		{ }

		bool SetPersonId(const string& personId) {
            _personId = personId;
            return true;
        }
 
		virtual bool isParaValid(ImageResult& result){
            if (! ReqBase::isParaValid(result))
                return false;

            if (_personId.empty()) {
				result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
				return false;
            }

			return true;
		}

        bool toJson(Json::Value& value) {
			value[PARA_PERSON_ID] = _personId;
            return true;
        }

        bool toForm(HttpForm& form) {
            return false;
        }

	protected:
        FaceGetInfoReq(){};

	protected:
        std::string _personId;
};

class FaceGetGroupIdsReq : public ReqBase
{
    public:
		FaceGetGroupIdsReq(const string& bucket)
			: ReqBase(bucket)
		{ }

		virtual bool isParaValid(ImageResult& result){
            if (! ReqBase::isParaValid(result))
                return false;

			return true;
		}

        bool toJson(Json::Value& value) {
            return true;
        }

        bool toForm(HttpForm& form) {
            return false;
        }

	protected:
        FaceGetGroupIdsReq(){};
};

class FaceGetPersonIdsReq : public ReqBase
{
    public:
		FaceGetPersonIdsReq(const string& bucket)
			: ReqBase(bucket)
		{ }

		bool SetGroupId(const string& groupId) {
            _groupId = groupId;
            return true;
        }
 
		virtual bool isParaValid(ImageResult& result){
            if (! ReqBase::isParaValid(result))
                return false;

            if (_groupId.empty()) {
				result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
				return false;
            }

			return true;
		}

        bool toJson(Json::Value& value) {
			value[PARA_GROUP_ID] = _groupId;
            return true;
        }

        bool toForm(HttpForm& form) {
            return false;
        }

	protected:
        FaceGetPersonIdsReq(){};

	protected:
        std::string _groupId;
};

class FaceGetFaceIdsReq : public ReqBase
{
    public:
		FaceGetFaceIdsReq(const string& bucket)
			: ReqBase(bucket)
		{ }

		bool SetPersonId(const string& personId) {
            _personId = personId;
            return true;
        }
 
		virtual bool isParaValid(ImageResult& result){
            if (! ReqBase::isParaValid(result))
                return false;

            if (_personId.empty()) {
				result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
				return false;
            }

			return true;
		}

        bool toJson(Json::Value& value) {
			value[PARA_PERSON_ID] = _personId;
            return true;
        }

        bool toForm(HttpForm& form) {
            return false;
        }

	protected:
        FaceGetFaceIdsReq(){};

	protected:
        std::string _personId;
};

class FaceGetFaceInfoReq : public ReqBase
{
    public:
		FaceGetFaceInfoReq(const string& bucket)
			: ReqBase(bucket)
		{ }

		bool SetFaceId(const string& faceId) {
            _faceId = faceId;
            return true;
        }
 
		virtual bool isParaValid(ImageResult& result){
            if (! ReqBase::isParaValid(result))
                return false;

            if (_faceId.empty()) {
				result.setCode(INVALID_PARAM);
				result.setMessage(INVALID_PARAM_DESC);
				return false;
            }

			return true;
		}

        bool toJson(Json::Value& value) {
			value[PARA_FACE_ID] = _faceId;
            return true;
        }

        bool toForm(HttpForm& form) {
            return false;
        }

	protected:
        FaceGetFaceInfoReq(){};

	protected:
        std::string _faceId;
};

}

#endif // FACE_REQ_H
