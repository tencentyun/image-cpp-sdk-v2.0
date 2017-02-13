#include "ImageApi.h"
#include <pthread.h>
#include <string>
#include "curl/curl.h"
using std::string;
namespace qcloud_image {

string ImageAPI::PornDetect(PornDetectReq& req){
    return _detectOp.PornDetect(req);
}

string ImageAPI::TagDetect(TagDetectReq& req){
    return _detectOp.TagDetect(req);
}

string ImageAPI::IdCardOcr(IdCardOcrReq& req){
    return _ocrOp.IdCardOcr(req);
}

string ImageAPI::NameCardOcr(NameCardOcrReq& req){
    return _ocrOp.NameCardOcr(req);
}

int ImageAPI::g_init = 0;
int ImageAPI::image_obj_num = 0;
SimpleMutex ImageAPI::init_mutex = SimpleMutex();

ImageAPI::ImageAPI(ImageConfig& config) : 
	_detectOp(config), _faceManagerOp(config), _faceOp(config), _ocrOp(config)
{
	Init();
}

ImageAPI::~ImageAPI(){
	Destory();
}

int ImageAPI::Init() {
    SimpleMutexLocker locker(&init_mutex);   
    ++image_obj_num;
    if (g_init) {
        return 0;
    }

    g_init = true;
    CURLcode retCode = curl_global_init(CURL_GLOBAL_ALL);
    if (CURLE_OK != retCode){
        std::cerr << "curl_global_init error:" << CURLE_OK << std::endl;
        return 1;
    }
    return 0;
}

void ImageAPI::Destory() {
    SimpleMutexLocker locker(&init_mutex);
    --image_obj_num;
    if (g_init && image_obj_num == 0) {
        curl_global_cleanup();
        g_init = false;
    }
}

string ImageAPI::FaceNewPerson(FaceNewPersonReq& req){
    return _faceManagerOp.NewPerson(req);
}
string ImageAPI::FaceDelPerson(FaceDelPersonReq& req){
    return _faceManagerOp.DelPerson(req);
}
string ImageAPI::FaceAddFace(FaceAddFaceReq& req){
    return _faceManagerOp.AddFace(req);
}
string ImageAPI::FaceDelFace(FaceDelFaceReq& req){
    return _faceManagerOp.DelFace(req);
}
string ImageAPI::FaceSetInfo(FaceSetInfoReq& req){
    return _faceManagerOp.SetInfo(req);
}
string ImageAPI::FaceGetInfo(FaceGetInfoReq& req){
    return _faceManagerOp.GetInfo(req);
}
string ImageAPI::FaceGetGroupIds(FaceGetGroupIdsReq& req){
    return _faceManagerOp.GetGroupIds(req);
}
string ImageAPI::FaceGetPersonIds(FaceGetPersonIdsReq& req){
    return _faceManagerOp.GetPersonIds(req);
}
string ImageAPI::FaceGetFaceIds(FaceGetFaceIdsReq& req){
    return _faceManagerOp.GetFaceIds(req);
}
string ImageAPI::FaceGetFaceInfo(FaceGetFaceInfoReq& req){
    return _faceManagerOp.GetFaceInfo(req);
}
string ImageAPI::FaceCompare(FaceCompareReq& req){
    return _faceOp.Compare(req);
}
string ImageAPI::FaceIdentify(FaceIdentifyReq& req){
    return _faceOp.Identify(req);
}
string ImageAPI::FaceVerify(FaceVerifyReq& req){
    return _faceOp.Verify(req);
}
string ImageAPI::FaceDetect(FaceDetectReq& req){
    return _faceOp.Detect(req);
}
string ImageAPI::FaceShape(FaceShapeReq& req){
    return _faceOp.Shape(req);
}

string ImageAPI::FaceIdCardCompare(FaceIdCardCompareReq& req){
    return _faceOp.IdCardCompare(req);
}  

string ImageAPI::FaceLiveGetFour(FaceLiveGetFourReq& req){
    return _faceOp.LiveGetFour(req);
} 

string ImageAPI::FaceLiveDetectFour(FaceLiveDetectFourReq& req){
    return _faceOp.LiveDetectFour(req);
}  

string ImageAPI::FaceIdCardLiveDetectFour(FaceIdCardLiveDetectFourReq& req){
    return _faceOp.IdCardLiveDetectFour(req);
}  

}
