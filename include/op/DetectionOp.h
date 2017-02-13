#ifndef FILE_OP_H
#define FILE_OP_H
#include "op/BaseOp.h"
#include "util/FileUtil.h"
#include "util/CodecUtil.h"
#include "util/HttpSender.h"
#include "request/PornDetectReq.h"
#include "request/TagDetectReq.h"
#include "ImageParams.h"
#include "ImageConfig.h"
#include "ImageSysConfig.h"
#include <string>

using std::string;
namespace qcloud_image{

class DetectionOp : public BaseOp {

    public:
        DetectionOp(ImageConfig& config)
		   	: BaseOp(config) 
		{};

        string PornDetect(PornDetectReq& req);
		string TagDetect(TagDetectReq& req);

	protected:
		string PornDetectUrl(PornDetectReq& req);
		string PornDetectImage(PornDetectReq& req);

		string TagDetectUrl(TagDetectReq& req);
		string TagDetectImage(TagDetectReq& req);
};

};


#endif
