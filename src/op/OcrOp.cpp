#include "op/OcrOp.h"
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

string OcrOp::IdCardOcr(IdCardOcrReq& req){
    ImageResult ret;
	if(!req.isParaValid(ret)){
		return ret.toJsonString();
	}

     if (!req.urls().empty()) {
        return IdCardOcrUrl(req);
    } else { 
        return IdCardOcrImage(req);
    }
}

string OcrOp::IdCardOcrUrl(IdCardOcrReq& req){
	string sign = Auth::AppSign(getAppid(), req.getBucket(), 
					getSecretID(), getSecretKey(), 
					ImageSysConfig::getAuthExpiredTime());
	//url
	string url = string("http://") + QCLOUD_IMAGE_DOMAIN + OCR_IDCARD; 
	//set header
	map<string,string> headers;
	headers[HTTP_HEADER_AUTHORIZATION] = sign;
    
	//set param
	map<string, string> params;
	params[PARA_APPID] = StringUtil::Uint64ToString(getAppid());
	params[PARA_BUCKET] = req.getBucket();
	params[CARD_TYPE] = StringUtil::Uint64ToString(req.card_type());
    
	return HttpSender::PostUrlList(url, headers, params, req.urls());
}

string OcrOp::IdCardOcrImage(IdCardOcrReq& req){
	string sign = Auth::AppSign(getAppid(), req.getBucket(),
				 getSecretID(), getSecretKey(),
				 ImageSysConfig::getAuthExpiredTime());

	//url
	string url = string("http://") + QCLOUD_IMAGE_DOMAIN + OCR_IDCARD;
	//set header
	map<string,string> headers;
	headers[HTTP_HEADER_AUTHORIZATION] = sign;
	//set param
	map<string, string> params;
	params[PARA_APPID] = StringUtil::Uint64ToString(getAppid());
	params[PARA_BUCKET] = req.getBucket();
    params[CARD_TYPE] = StringUtil::Uint64ToString(req.card_type());

     if (!req.images().empty()) {
        for(map<string, string>::const_iterator it = req.images().begin(); 
            it != req.images().end(); it++){
            req.AddBuffer(it->first, FileUtil::getFileContent(it->second));
        }
    }       
    
	return HttpSender::PostImageList(url, headers, params, req.buffers());
}

string OcrOp::NameCardOcr(NameCardOcrReq& req){
    ImageResult ret;
	if(!req.isParaValid(ret)){
		return ret.toJsonString();
	}

    if (!req.urls().empty()) {
        return NameCardOcrUrl(req);
    } else { 
        return NameCardOcrImage(req);
    } 
}

string OcrOp::NameCardOcrUrl(NameCardOcrReq& req){
	string sign = Auth::AppSign(getAppid(), req.getBucket(), 
					getSecretID(), getSecretKey(), 
					ImageSysConfig::getAuthExpiredTime());
	//url
	string url = string("http://") + QCLOUD_IMAGE_DOMAIN + OCR_NAMECARD; 
	//set header
	map<string,string> headers;
	headers[HTTP_HEADER_AUTHORIZATION] = sign;
	//set param
	map<string, string> params;
	params[PARA_APPID] = StringUtil::Uint64ToString(getAppid());
	params[PARA_BUCKET] = req.getBucket();
	params[RET_IMAGE] = StringUtil::Uint64ToString(req.ret_image());
    
	return HttpSender::PostUrlList(url, headers, params, req.urls());
}

string OcrOp::NameCardOcrImage(NameCardOcrReq& req){
	string sign = Auth::AppSign(getAppid(), req.getBucket(),
				 getSecretID(), getSecretKey(),
				 ImageSysConfig::getAuthExpiredTime());

	//url
	string url = string("http://") + QCLOUD_IMAGE_DOMAIN + OCR_NAMECARD;
	//set header
	map<string,string> headers;
	headers[HTTP_HEADER_AUTHORIZATION] = sign;
	//set param
	map<string, string> params;
	params[PARA_APPID] = StringUtil::Uint64ToString(getAppid());
	params[PARA_BUCKET] = req.getBucket();
    params[RET_IMAGE] =  StringUtil::Uint64ToString(req.ret_image());
	
    if (!req.images().empty()) {
        for(map<string, string>::const_iterator it = req.images().begin(); 
            it != req.images().end(); it++){
            req.AddBuffer(it->first, FileUtil::getFileContent(it->second));
        }
    }       
    
	return HttpSender::PostImageList(url, headers, params, req.buffers());
}


}

