#ifndef FACE_OP_H
#define FACE_OP_H

#include "op/BaseOp.h"
#include "util/FileUtil.h"
#include "util/CodecUtil.h"
#include "util/HttpSender.h"
#include "request/FaceReq.h"
#include "ImageParams.h"
#include "ImageConfig.h"
#include "ImageSysConfig.h"
#include <string>

using std::string;
namespace qcloud_image{

class FaceOp : public BaseOp {

    public:
        FaceOp(ImageConfig& config)
		   	: BaseOp(config) 
		{};

        string Compare(FaceCompareReq& req);
        string Identify(FaceIdentifyReq& req);
        string Verify(FaceVerifyReq& req);
        string Detect(FaceDetectReq& req);
        string Shape(FaceShapeReq& req);

        string IdCardCompare(FaceIdCardCompareReq& req);
        string LiveGetFour(FaceLiveGetFourReq& req);
        string LiveDetectFour(FaceLiveDetectFourReq& req);
        string IdCardLiveDetectFour(FaceIdCardLiveDetectFourReq& req);
};

};

#endif // FACE_OP_H
