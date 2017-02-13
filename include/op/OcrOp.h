#ifndef OCR_OP_H
#define OCR_OP_H
#include "op/BaseOp.h"
#include "util/FileUtil.h"
#include "util/CodecUtil.h"
#include "util/HttpSender.h"
#include "request/OcrReq.h"
#include "ImageParams.h"
#include "ImageConfig.h"
#include "ImageSysConfig.h"
#include <string>

using std::string;
namespace qcloud_image{

class OcrOp : public BaseOp {

    public:
        OcrOp(ImageConfig& config)
		   	: BaseOp(config) 
		{};

        string IdCardOcr(IdCardOcrReq& req);
        string NameCardOcr(NameCardOcrReq& req);
		
	protected:
		string IdCardOcrUrl(IdCardOcrReq& req);
		string IdCardOcrImage(IdCardOcrReq& req);
		
		string NameCardOcrUrl(NameCardOcrReq& req);
		string NameCardOcrImage(NameCardOcrReq& req);
};

};


#endif // OCR_OP_H
