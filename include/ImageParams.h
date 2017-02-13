#ifndef IMAGE_PARAMS_H
#define IMAGE_PARAMS_H

namespace qcloud_image{

const string HTTP_HEADER_AUTHORIZATION = "Authorization";
const string HTTP_HEADER_HOST = "HOST";

const string PARA_APPID       = "appid";
const string PARA_BUCKET      = "bucket";
const string PARA_URL_LIST    = "url_list";
const string PARA_URL         = "url";
const string PARA_URLA        = "urlA";
const string PARA_URLB        = "urlB";
const string PARA_URLS        = "urls";
const string PARA_IMAGE       = "image";
const string PARA_IMAGEA      = "imageA";
const string PARA_IMAGEB      = "imageB";
const string PARA_IMAGES      = "images";
const string PARA_GROUP_ID    = "group_id";
const string PARA_GROUP_IDS   = "group_ids";
const string PARA_PERSON_ID   = "person_id";
const string PARA_PERSON_NAME = "person_name";
const string PARA_FACE_IDS    = "face_ids";
const string PARA_FACE_ID     = "face_id";
const string PARA_TAG         = "tag";
const string PARA_IDCARD_NUMBER = "idcard_number";
const string PARA_IDCARD_NAME   = "idcard_name";
const string PARA_SESSION_ID    = "session_id";
const string PARA_SEQ           = "seq";
const string PARA_VALIDATE_DATA = "validate_data";
const string PARA_VIDEO         = "video";
const string PARA_COMPARE_FLAG  = "compare_flag";
const string PARA_CARD          = "card";
const string PARA_MODE          = "mode";
const string CARD_TYPE          = "card_type";
const string RET_IMAGE          = "ret_image";




#define SYMBOL_FILE "@file@"
const string INVALID_PARAM_DESC = "invalid param";
const string IMAGE_EXCEED_LIMIT_DESC = "image exceed limit";
const string NETWORK_ERROR_DESC = "network error";
const string LOCAL_FILE_NOT_EXIST_DESC = "file "SYMBOL_FILE" not exist";

enum ImageRetCode{
	SUCCESS = 0,
	INVALID_PARAM = -1,
	IMAGE_EXCEED_LIMIT = -2,
    NETWORK_ERROR = -3,
    LOCAL_FILE_NOT_EXIST = -4
};

}

#endif
