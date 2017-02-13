#ifndef FACE_MANAGER_OP_H
#define FACE_MANAGER_OP_H

#include "op/BaseOp.h"
#include "util/FileUtil.h"
#include "util/CodecUtil.h"
#include "util/HttpSender.h"
#include "request/FaceManagerReq.h"
#include "ImageParams.h"
#include "ImageConfig.h"
#include "ImageSysConfig.h"
#include <string>

using std::string;
namespace qcloud_image{

class FaceManagerOp : public BaseOp {

    public:
        FaceManagerOp(ImageConfig& config)
		   	: BaseOp(config) 
		{};

        string NewPerson(FaceNewPersonReq& req);
        string DelPerson(FaceDelPersonReq& req);
        string AddFace(FaceAddFaceReq& req);
        string DelFace(FaceDelFaceReq& req);
        string SetInfo(FaceSetInfoReq& req);
        string GetInfo(FaceGetInfoReq& req);
        string GetGroupIds(FaceGetGroupIdsReq& req);
        string GetPersonIds(FaceGetPersonIdsReq& req);
        string GetFaceIds(FaceGetFaceIdsReq& req);
        string GetFaceInfo(FaceGetFaceInfoReq& req);
};

};

#endif // FACE_MANAGER_OP_H
