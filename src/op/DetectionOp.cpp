#include "op/DetectionOp.h"
#include "request/ImageResult.h"
#include "util/CodecUtil.h"
#include "util/StringUtil.h"
#include "util/FileUtil.h"
#include "ImageDefines.h"
#include "Auth.h"
#include <string.h>
#include <stdint.h>
#include <map>
#include <string>

using namespace std;
namespace qcloud_image{

string DetectionOp::PornDetect(PornDetectReq& req){
	ImageResult ret;
	if (!req.isParaValid(ret)) {
		return ret.toJsonString();
	}

    if (!req.urls().empty()) {
        return PornDetectUrl(req);
    } else { 
        return PornDetectImage(req);
    }
}

string DetectionOp::PornDetectUrl(PornDetectReq& req){
	string sign = Auth::AppSign(getAppid(), req.getBucket(), 
					getSecretID(), getSecretKey(), 
					ImageSysConfig::getAuthExpiredTime());
	//url
	string url = string("http://") + QCLOUD_IMAGE_DOMAIN + DETECTION_PORN; 
	//set header
	map<string,string> headers;
	headers[HTTP_HEADER_AUTHORIZATION] = sign;
	//set param
	map<string, string> params;
	params[PARA_APPID] = StringUtil::Uint64ToString(getAppid());
	params[PARA_BUCKET] = req.getBucket();
	
	return HttpSender::PostUrlList(url, headers, params, req.urls());
}

string DetectionOp::PornDetectImage(PornDetectReq& req){
	string sign = Auth::AppSign(getAppid(), req.getBucket(),
				 getSecretID(), getSecretKey(),
				 ImageSysConfig::getAuthExpiredTime());

	//url
	string url = string("http://") + QCLOUD_IMAGE_DOMAIN + DETECTION_PORN;
	//set header
	map<string,string> headers;
	headers[HTTP_HEADER_AUTHORIZATION] = sign;
	//set param
	map<string, string> params;
	params[PARA_APPID] = StringUtil::Uint64ToString(getAppid());
	params[PARA_BUCKET] = req.getBucket();
    
    if (!req.images().empty()) {
        for(map<string, string>::const_iterator it = req.images().begin(); 
            it != req.images().end(); it++){
            req.AddBuffer(it->first, FileUtil::getFileContent(it->second));
        }
    }       
    
	return HttpSender::PostImageList(url, headers, params, req.buffers());
}

string DetectionOp::TagDetect(TagDetectReq& req){
	ImageResult ret;
	if (!req.isParaValid(ret)) {
		return ret.toJsonString();
	}

    if (!req.url().empty()) {
        return TagDetectUrl(req);
    } else {
        return TagDetectImage(req);
    }
}

string DetectionOp::TagDetectUrl(TagDetectReq& req){
	string sign = Auth::AppSign(getAppid(), req.getBucket(), 
					getSecretID(), getSecretKey(), 
					ImageSysConfig::getAuthExpiredTime());
	//url
	string url = string("http://") + QCLOUD_IMAGE_DOMAIN + DETECTION_TAG; 
	//set header
	map<string,string> headers;
	headers[HTTP_HEADER_AUTHORIZATION] = sign;
    
	//set param
	Json::Value params;
	params[PARA_APPID] = StringUtil::Uint64ToString(getAppid());
	params[PARA_BUCKET] = req.getBucket();
    params[PARA_URL] = req.url();

    return HttpSender::PostJsonReq(url, headers, params);
}

string DetectionOp::TagDetectImage(TagDetectReq& req){
	string sign = Auth::AppSign(getAppid(), req.getBucket(),
				 getSecretID(), getSecretKey(),
				 ImageSysConfig::getAuthExpiredTime());

	//url
	string url = string("http://") + QCLOUD_IMAGE_DOMAIN + DETECTION_TAG;
	//set header
	map<string,string> headers;
	headers[HTTP_HEADER_AUTHORIZATION] = sign;
    
	//set param
	Json::Value params;
	params[PARA_APPID] = StringUtil::Uint64ToString(getAppid());
	params[PARA_BUCKET] = req.getBucket();
    if (!req.image().empty()) {
        params[PARA_IMAGE] = CodecUtil::Base64Encode(FileUtil::getFileContent(req.image()));
    } else {
        params[PARA_IMAGE] = CodecUtil::Base64Encode(req.buffer());
    }
	
	return HttpSender::PostJsonReq(url, headers, params);
}
}

