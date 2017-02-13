#include "op/FaceManagerOp.h"
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

#define FaceManagerOpFunc_Impl(FUNC, API) string FaceManagerOp::FUNC(Face##FUNC##Req& req){ \
	ImageResult ret; \
	if (! req.isParaValid(ret)) { \
		return ret.toJsonString(); \
	} \
\
	string url = string("http://") + QCLOUD_IMAGE_DOMAIN + API; \
\
	map<string,string> headers; \
	headers[HTTP_HEADER_HOST] = QCLOUD_IMAGE_HOST; \
	string sign = Auth::AppSign(getAppid(), req.getBucket(), \
					getSecretID(), getSecretKey(), \
					ImageSysConfig::getAuthExpiredTime()); \
	headers[HTTP_HEADER_AUTHORIZATION] = sign; \
\
    Json::Value value; \
    if (req.toJson(value)) \
    { \
        value[PARA_APPID] = StringUtil::Uint64ToString(getAppid()); \
        value[PARA_BUCKET] = req.getBucket(); \
        return HttpSender::PostJsonReq(url, headers, value); \
    } \
\
    HttpForm form; \
    if (req.toForm(form)) \
    { \
        form[PARA_APPID] = std::make_pair(StringUtil::Uint64ToString(getAppid()), false); \
        form[PARA_BUCKET] = std::make_pair(req.getBucket(), false); \
        return HttpSender::PostFormReq(url, headers, form); \
    } \
\
    ret.setCode(INVALID_PARAM); \
    ret.setMessage(INVALID_PARAM_DESC); \
    return ret.toJsonString(); \
}

FaceManagerOpFunc_Impl(NewPerson, API_FACE_NEW_PERSON);
FaceManagerOpFunc_Impl(DelPerson, API_FACE_DEL_PERSON);
FaceManagerOpFunc_Impl(AddFace, API_FACE_ADD_FACE);
FaceManagerOpFunc_Impl(DelFace, API_FACE_DEL_FACE);
FaceManagerOpFunc_Impl(SetInfo, API_FACE_SET_INFO);
FaceManagerOpFunc_Impl(GetInfo, API_FACE_GET_INFO);
FaceManagerOpFunc_Impl(GetGroupIds, API_FACE_GET_GROUP_IDS);
FaceManagerOpFunc_Impl(GetPersonIds, API_FACE_GET_PERSON_IDS);
FaceManagerOpFunc_Impl(GetFaceIds, API_FACE_GET_FACE_IDS);
FaceManagerOpFunc_Impl(GetFaceInfo, API_FACE_GET_FACE_INFO);

}

