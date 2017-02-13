#include "op/FaceOp.h"
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

#define FaceOpFunc_Impl(FUNC, API) string FaceOp::FUNC(Face##FUNC##Req& req){ \
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

FaceOpFunc_Impl(Compare, API_FACE_COMPARE);
FaceOpFunc_Impl(Identify, API_FACE_IDENTIFY);
FaceOpFunc_Impl(Verify, API_FACE_VERIFY);
FaceOpFunc_Impl(Detect, API_FACE_DETECT);
FaceOpFunc_Impl(Shape, API_FACE_SHAPE);

FaceOpFunc_Impl(IdCardCompare, API_FACE_IDCARD_COMPARE);
FaceOpFunc_Impl(LiveGetFour, API_FACE_LIVE_GET_FOUR);
FaceOpFunc_Impl(LiveDetectFour, API_FACE_LIVE_DETECT_FOUR);
FaceOpFunc_Impl(IdCardLiveDetectFour, API_FACE_IDCARD_LIVE_DETECT_FOUR);

}

