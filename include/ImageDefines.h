#ifndef IMAGE_DEFINE_H
#define IMAGE_DEFINE_H
#include <string>
#include <map>
using std::string;

#define QCLOUD_IMAGE_DOMAIN		"service.image.myqcloud.com"
#define QCLOUD_IMAGE_HOST		"service.image.myqcloud.com"

#define MAX_DETECTION_NUM		20
#define DETECTION_PORN			"/detection/porn_detect"
#define OCR_IDCARD				"/ocr/idcard"
#define OCR_NAMECARD			"/ocr/namecard"
#define DETECTION_TAG			"/v1/detection/imagetag_detect"
#define API_FACE_COMPARE        "/face/compare"
#define API_FACE_IDENTIFY       "/face/identify"
#define API_FACE_VERIFY         "/face/verify"
#define API_FACE_DETECT         "/face/detect"
#define API_FACE_SHAPE          "/face/shape"
#define API_FACE_NEW_PERSON     "/face/newperson"
#define API_FACE_DEL_PERSON     "/face/delperson"
#define API_FACE_ADD_FACE       "/face/addface"
#define API_FACE_DEL_FACE       "/face/delface"
#define API_FACE_SET_INFO       "/face/setinfo"
#define API_FACE_GET_INFO       "/face/getinfo"
#define API_FACE_GET_GROUP_IDS  "/face/getgroupids"
#define API_FACE_GET_PERSON_IDS "/face/getpersonids"
#define API_FACE_GET_FACE_IDS   "/face/getfaceids"
#define API_FACE_GET_FACE_INFO  "/face/getfaceinfo"
#define API_FACE_IDCARD_COMPARE          "/face/idcardcompare"
#define API_FACE_LIVE_GET_FOUR           "/face/livegetfour"
#define API_FACE_LIVE_DETECT_FOUR        "/face/livedetectfour"
#define API_FACE_IDCARD_LIVE_DETECT_FOUR "/face/idcardlivedetectfour"

namespace qcloud_image{

typedef std::map<std::string, std::pair<std::string, bool> > HttpForm;
typedef std::map<std::string, std::pair<std::string, bool> >::iterator HttpFormIter;
typedef std::map<std::string, std::pair<std::string, bool> >::const_iterator HttpFormConstIter;

const string kPathDelimiter = "/";
const unsigned char kPathDelimiterChar = '/';
// 默认的外部地址
// 分片上传时，失败的最大重试次数
const int kMaxRetryTimes = 3;

const int SINGLE_FILE_SIZE = 8 * 1024 * 1024;

}
#endif
