#ifndef IMAGE_API_H
#define IMAGE_API_H
#include "request/PornDetectReq.h"
#include "request/FaceManagerReq.h"
#include "request/FaceReq.h"
#include "request/OcrReq.h"
#include "op/DetectionOp.h"
#include "op/FaceManagerOp.h"
#include "op/FaceOp.h"
#include "op/OcrOp.h"
#include "ImageConfig.h"
#include "util/SimpleMutex.h"
#include <string>
#include <stdint.h>
using namespace std;
namespace qcloud_image{

class ImageAPI
{
    public:
        ImageAPI(ImageConfig& config);
        ~ImageAPI();

		//黄图检测
		string PornDetect(PornDetectReq& req);
		string TagDetect(TagDetectReq& req);
        string FaceNewPerson(FaceNewPersonReq& req);
        string FaceDelPerson(FaceDelPersonReq& req);
        string FaceAddFace(FaceAddFaceReq& req);
        string FaceDelFace(FaceDelFaceReq& req);
        string FaceSetInfo(FaceSetInfoReq& req);
        string FaceGetInfo(FaceGetInfoReq& req);
        string FaceGetGroupIds(FaceGetGroupIdsReq& req);
        string FaceGetPersonIds(FaceGetPersonIdsReq& req);
        string FaceGetFaceIds(FaceGetFaceIdsReq& req);
        string FaceGetFaceInfo(FaceGetFaceInfoReq& req);

        string FaceCompare(FaceCompareReq& req);
        string FaceIdentify(FaceIdentifyReq& req);
        string FaceVerify(FaceVerifyReq& req);
        string FaceDetect(FaceDetectReq& req);
        string FaceShape(FaceShapeReq& req);
		string IdCardOcr(IdCardOcrReq& req);
		string NameCardOcr(NameCardOcrReq& req);
		string FaceIdCardCompare(FaceIdCardCompareReq& req);
		string FaceLiveGetFour(FaceLiveGetFourReq& req);		
		string FaceLiveDetectFour(FaceLiveDetectFourReq& req);
		string FaceIdCardLiveDetectFour(FaceIdCardLiveDetectFourReq& req);

    private:
        int Init();
        void Destory();

    private:
		DetectionOp		_detectOp;
        FaceManagerOp   _faceManagerOp;
        FaceOp          _faceOp;
        OcrOp           _ocrOp;
        
		static SimpleMutex init_mutex;
        static int g_init;
        static int image_obj_num;
};


}
#endif
