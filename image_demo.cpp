#include "ImageApi.h"
#include "request/PornDetectReq.h"
#include "ImageConfig.h"
#include "ImageParams.h"
#include "ImageSysConfig.h"
#include "util/StringUtil.h"
#include <stdint.h>
#include <iostream>
#include <string>

using namespace std;
using namespace qcloud_image;

#define APP_ID	YOUR_APPID	
#define SECRET_ID	"YOUR_SECRETID"
#define SECRET_KEY	"YOUR_SECRETKEY"
#define BUCKET		"YOUR_BUCKET"

int main(int argc, char* argv[]){
    //设置全局参数（非必须）
    ImageSysConfig::setAuthExpiredTime(300); //设置签名超时时长300s

    //生成ImageAPI对象
    ImageConfig config(APP_ID, SECRET_ID, SECRET_KEY);
    ImageAPI image(config);
    string ret = "";

	//黄图识别
	//单个或多个图片Url
	cout<<"===================================================="<<endl;
	cout<<"PornDetect"<<endl;
	PornDetectReq pornReq(BUCKET);
    pornReq.AddUrl("http://hearthstone.nos.netease.com/1/artworkGvG/GoblinBlastmagel.jpg");
    pornReq.AddUrl("http://hearthstone.nos.netease.com/1/artworkGvG/Faerlinal.jpg");
    pornReq.AddUrl("http://hearthstone.nos.netease.com/1/artworkGvG/KelThuzadl.jpg");
	ret = image.PornDetect(pornReq);
	cout<<ret<<endl;
    
    //单个或多个图片File
	PornDetectReq pornReq2(BUCKET);
    pornReq2.AddImage("test2.jpg","test2.jpg");
    pornReq2.AddImage("test1.jpg","test1.jpg");
	ret = image.PornDetect(pornReq2);
	cout<<ret<<endl;  
	
	//单个或多个图片内容
    PornDetectReq pornReq3(BUCKET);
    pornReq3.AddBuffer("test1.jpg",FileUtil::getFileContent("test1.jpg"));
    pornReq3.AddBuffer("test2.jpg",FileUtil::getFileContent("test2.jpg"));
	ret = image.PornDetect(pornReq3);
	cout<<ret<<endl;  


	///身份证识别
	//单个或多个图片Url,识别身份证正面
	cout<<"===================================================="<<endl;
	cout<<"IdCardOcr"<<endl;
	IdCardOcrReq idReq1(BUCKET);
    idReq1.AddUrl("http://imgs.focus.cn/upload/sz/5876/a_58758051.jpg");
    idReq1.AddUrl("http://img5.iqilu.com/c/u/2013/0530/1369896921237.jpg");
    idReq1.SetCardType(0);
	ret = image.IdCardOcr(idReq1);
	cout<<ret<<endl;
    
	//单个或多个图片file,识别身份证正面
    IdCardOcrReq idReq2(BUCKET);
    idReq2.AddImage("id6_zheng.jpg","id6_zheng.jpg");
    idReq2.AddImage("id2_zheng.jpg","id2_zheng.jpg");
    idReq2.SetCardType(0);
	ret = image.IdCardOcr(idReq2);
	cout<<ret<<endl;

	//单个或多个图片内容,识别身份证正面
    IdCardOcrReq idReq3(BUCKET);
    idReq3.AddBuffer("id6_zheng.jpg", FileUtil::getFileContent("id6_zheng.jpg"));
    idReq3.AddBuffer("id2_zheng.jpg", FileUtil::getFileContent("id2_zheng.jpg"));
    idReq3.SetCardType(0);
	ret = image.IdCardOcr(idReq3);
	cout<<ret<<endl;

	//单个或多个图片Url,识别身份证反面
    IdCardOcrReq idReq4(BUCKET);
    idReq4.AddUrl("http://www.csx.gov.cn/cwfw/bszn/201403/W020121030349825312574.jpg");
    idReq4.AddUrl("http://www.4009951551.com/upload/image/20151026/1445831136187479.png");
    idReq4.SetCardType(1);
	ret = image.IdCardOcr(idReq4);
	cout<<ret<<endl;

	//单个或多个图片内容,识别身份证反面
    IdCardOcrReq idReq5(BUCKET);
    idReq5.AddBuffer("id5_fan.jpg", FileUtil::getFileContent("id5_fan.jpg"));
    idReq5.AddBuffer("id7_fan.jpg", FileUtil::getFileContent("id7_fan.jpg"));
    idReq5.SetCardType(1);
	ret = image.IdCardOcr(idReq5);
	cout<<ret<<endl;

	//名片识别
	//单个或多个图片Url
	cout<<"===================================================="<<endl;
	cout<<"NameCardOcr"<<endl;
    NameCardOcrReq nameReq1(BUCKET);
    nameReq1.AddUrl("http://imgs.focus.cn/upload/sz/5876/a_58758051.jpg");
    nameReq1.AddUrl("http://img5.iqilu.com/c/u/2013/0530/1369896921237.jpg");
    nameReq1.setRetImage(0);
	ret = image.NameCardOcr(nameReq1);
	cout<<ret<<endl;

	//单个或多个图片file
    NameCardOcrReq nameReq2(BUCKET);
    nameReq2.AddImage("name2.jpg","name2.jpg");
    nameReq2.AddImage("r.jpg","r.jpg");
    nameReq2.setRetImage(1);
	ret = image.NameCardOcr(nameReq2);
	cout<<ret<<endl;
	
	//单个或多个图片内容
    NameCardOcrReq nameReq3(BUCKET);
    nameReq3.AddBuffer("name2.jpg",FileUtil::getFileContent("name2.jpg"));
    nameReq3.AddBuffer("r.jpg",FileUtil::getFileContent("r.jpg"));
    nameReq3.setRetImage(0);
    ret = image.NameCardOcr(nameReq3);
    cout<<ret<<endl;

	//图片标签
	//单个图片url
	cout<<"===================================================="<<endl;
	cout<<"TagDetect"<<endl;
	TagDetectReq tagReq(BUCKET);
	tagReq.SetUrl("http://img3.a0bi.com/upload/ttq/20160814/1471155260063.png");
	ret = image.TagDetect(tagReq);
	cout<<ret<<endl;

	//单个图片file
	TagDetectReq tagReq1(BUCKET);
	tagReq1.SetImage("hot1.jpg");
	ret = image.TagDetect(tagReq1);
	cout<<ret<<endl;

    //单个图片内容
	TagDetectReq tagReq2(BUCKET);
	tagReq2.SetBuffer(FileUtil::getFileContent("hot1.jpg"));
	ret = image.TagDetect(tagReq2);
	cout<<ret<<endl;

    //人脸检测
	//单个图片Url, mode:1为检测最大的人脸 , 0为检测所有人脸
	cout << "====================================================" << endl;
    cout << "Face Detect" << endl;
    FaceDetectReq faceDetectReq(BUCKET);
    faceDetectReq.SetMode(0);
    faceDetectReq.SetUrl("http://burningtest-10006599.cosgz.myqcloud.com/laobao.jpg");
    ret = image.FaceDetect(faceDetectReq);
    cout<<ret<<endl; 

    //单个图片file
    FaceDetectReq faceDetectReq1(BUCKET);
    faceDetectReq1.SetImage("zhao2.jpg");
    ret = image.FaceDetect(faceDetectReq1);
	cout<<ret<<endl; 


	//五官定位
	//单个图片Url,检测最大的人脸
	cout << "====================================================" << endl;
    cout << "Face Shape" << endl;
    FaceShapeReq faceShapeReq(BUCKET);
    faceShapeReq.SetMode(0);
    faceShapeReq.SetUrl("http://burningtest-10006599.cosgz.myqcloud.com/laobao.jpg");
    ret = image.FaceShape(faceShapeReq);
    cout<<ret<<endl; 

 	//单个图片file
 	FaceShapeReq faceShapeReq1(BUCKET);
    faceShapeReq1.SetMode(0);
    faceShapeReq1.SetImage("zhao2.jpg");
    ret = image.FaceShape(faceShapeReq1);
	cout<<ret<<endl; 

	//创建一个Person，并将Person放置到group_ids指定的组当中, 使用图片url
	cout << "====================================================" << endl;
    cout << "New Person" << endl;
    FaceNewPersonReq newPersonReq(BUCKET);
    newPersonReq.SetUrl("http://img3.a0bi.com/upload/ttq/20160814/1471155260063.png");
    newPersonReq.SetPersonId("person2222");
    newPersonReq.AddGroupId("group2222");
    ret = image.FaceNewPerson(newPersonReq);
    cout<<ret<<endl; 

 	//单个图片file
 	FaceNewPersonReq newPersonReq1(BUCKET);
 	newPersonReq1.SetPersonId("person3333");
    newPersonReq1.SetImage("zhao2.jpg");
    newPersonReq1.AddGroupId("group2222");
    ret = image.FaceNewPerson(newPersonReq1);
	cout<<ret<<endl; 

	//增加人脸,将单个或者多个Face的url加入到一个Person中.注意，一个Face只能被加入到一个Person中。 一个Person最多允许包含20个Face
	cout << "====================================================" << endl;
    cout << "Add Face" << endl;
    FaceAddFaceReq addFaceReq(BUCKET);
    addFaceReq.AddUrl("http://jiangsu.china.com.cn/uploadfile/2015/1102/1446443026382534.jpg");
    addFaceReq.AddUrl("http://n.sinaimg.cn/fashion/transform/20160704/flgG-fxtspsa6612705.jpg");
    addFaceReq.SetPersonId("person2222");
    ret = image.FaceAddFace(addFaceReq);
    cout<<ret<<endl; 

 	//增加人脸,将单个或者多个Face的file加入到一个Person中
    FaceAddFaceReq addFaceReq1(BUCKET);
    addFaceReq1.AddImage("zhao1.jpg");
    addFaceReq1.AddImage("zhao2.jpg");
    addFaceReq1.SetPersonId("person2222");
    ret = image.FaceAddFace(addFaceReq1);
	cout<<ret<<endl; 


	//删除人脸
	cout << "====================================================" << endl;
    cout  << "DelFace" << endl;
    FaceDelFaceReq delFaceReq(BUCKET);
    delFaceReq.SetPersonId("person2222");
    delFaceReq.AddFaceId("1831408218312574949");
    delFaceReq.AddFaceId("1831408248150847230");
    ret = image.FaceDelFace(delFaceReq);
    cout<<ret<<endl; 


    //设置信息
	cout << "====================================================" << endl;
    cout << "Set Info" << endl;
    FaceSetInfoReq setInfoReq(BUCKET);
    setInfoReq.SetPersonId("person2222");
    setInfoReq.SetPersonName("ying");
    ret = image.FaceSetInfo(setInfoReq);
    cout<<ret<<endl;


    //获取信息
	cout << "====================================================" << endl;
    cout << "Get Info" << endl;
    FaceGetInfoReq getInfoReq(BUCKET);
    getInfoReq.SetPersonId("person2222");
    ret = image.FaceGetInfo(getInfoReq);
    cout<<ret<<endl;


    //获取组列表
	cout << "====================================================" << endl;
    cout << "Get GroupId info" << endl;
    FaceGetGroupIdsReq getGroupIdReq(BUCKET);
    ret = image.FaceGetGroupIds(getGroupIdReq);
    cout<<ret<<endl;


    //获取人列表
	cout << "====================================================" << endl;
    cout   << "Get PersonId Info" << endl;
    FaceGetPersonIdsReq getPersonIdReq(BUCKET);
    getPersonIdReq.SetGroupId("group2222");
    ret = image.FaceGetPersonIds(getPersonIdReq);
    cout<<ret<<endl;


    //获取人脸列表
	cout << "====================================================" << endl;
    cout   << "Get faceId Id" << endl;
    FaceGetFaceIdsReq getFaceIdReq(BUCKET);
    getFaceIdReq.SetPersonId("person2222");
    ret = image.FaceGetFaceIds(getFaceIdReq);
    cout<<ret<<endl;


    //获取人脸信息
	cout << "====================================================" << endl;
    cout  << "Get faceId Info" << endl;
    FaceGetFaceInfoReq getFaceInfoReq(BUCKET);
    getFaceInfoReq.SetFaceId("1704147773393235686");
    ret = image.FaceGetFaceInfo(getFaceInfoReq);
    cout<<ret<<endl;

    ////删除个人
	cout << "====================================================" << endl;
    cout << "Face Del Person" << endl;
    FaceDelPersonReq delPersonReq(BUCKET);
    delPersonReq.SetPersonId("person2222");
    ret = image.FaceDelPerson(delPersonReq);
    cout<<ret<<endl;


    //人脸验证
	//单个图片Url
    cout << "====================================================" << endl;
    cout << "Face Verify" << endl;
    FaceVerifyReq faceVerifyReq(BUCKET);
    faceVerifyReq.SetUrl("http://img3.a0bi.com/upload/ttq/20160814/1471155260063.png");
    faceVerifyReq.SetPersonId("person1");
    ret = image.FaceVerify(faceVerifyReq);
    cout<<ret<<endl; 

    //单个图片file
    FaceVerifyReq faceVerifyReq1(BUCKET);
    faceVerifyReq1.SetImage("yang3.jpg");
    ret = image.FaceVerify(faceVerifyReq1);
	cout<<ret<<endl;  


	 //人脸检索
	//单个图片Url
    cout << "====================================================" << endl;
    cout << "Face Identify" << endl;
    FaceIdentifyReq identifyReq(BUCKET);
    identifyReq.SetUrl("http://img3.a0bi.com/upload/ttq/20160814/1471155260063.png");
    identifyReq.SetGroupId("group2222");
    ret = image.FaceIdentify(identifyReq);
    cout<<ret<<endl; 

    //单个图片file
    FaceIdentifyReq identifyReq1(BUCKET);
    identifyReq1.SetGroupId("group2222");
    identifyReq1.SetImage("yang3.jpg");
    ret = image.FaceIdentify(identifyReq1);
	cout<<ret<<endl;  


	//人脸对比
	//两个对比图片的文件url
    cout << "====================================================" << endl;
    cout << "Face Compare" << endl;
    FaceCompareReq fcReq(BUCKET);
    fcReq.AddUrl("http://burningtest-10006599.cosgz.myqcloud.com/laobao.jpg");
    fcReq.AddUrl("http://burningtest-10006599.cosgz.myqcloud.com/laobao.jpg");
    ret = image.FaceCompare(fcReq);
    cout<<ret<<endl; 

    //两个对比图片的文件file
    FaceCompareReq fcReq1(BUCKET);
    fcReq1.AddImage("zhao1.jpg");
    fcReq1.AddImage("zhao2.jpg");
    ret = image.FaceCompare(fcReq1);
	cout<<ret<<endl;  


	//身份证识别对比
	//身份证url
	cout << "====================================================" << endl;
    cout<< "Face IdCard compare" << endl;
    FaceIdCardCompareReq idCompareReq(BUCKET);
    idCompareReq.SetUrl("http://docs.ebdoor.com/Image/CompanyCertificate/1/16844.jpg");
    idCompareReq.SetIdCardNumber("330782198802084329");
    idCompareReq.SetIdCardName("季锦锦");
    ret = image.FaceIdCardCompare(idCompareReq);

    FaceIdCardCompareReq idCompareReq1(BUCKET);
    idCompareReq1.SetIdCardNumber("330782198802084329");
    idCompareReq1.SetIdCardName("季锦锦");
    idCompareReq1.SetImage("idcard.jpg");
    ret = image.FaceIdCardCompare(idCompareReq1);
    cout<<ret<<endl; 

    ////人脸核身
	//活体检测第一步：获取唇语（验证码）
	cout << "====================================================" << endl;
    cout<< "Face Live Get Four" << endl;
    FaceLiveGetFourReq getFourReq(BUCKET);
    ret = image.FaceLiveGetFour(getFourReq);
    cout<<ret<<endl; 
    string validate = "";
    Json::Value obj = StringUtil::StringToJson(ret);

    Json::FastWriter json_writer;
    string data = json_writer.write(obj["data"]);
    if (!data.empty()) {
        Json::Value dataObj = StringUtil::StringToJson(data);
        validate =json_writer.write(dataObj["validate_data"]);
    }

    //活体检测第二步：检测
    cout << "====================================================" << endl;
    cout<< "Face Live Detect Four " << endl;
    FaceLiveDetectFourReq detectFourReq(BUCKET);
    detectFourReq.SetValidateData(validate);
    detectFourReq.SetVideo("ZOE_0171.mp4");
    ret = image.FaceLiveDetectFour(detectFourReq);
    cout<<ret<<endl; 

    //活体检测第二步：检测--对比指定身份信息
    cout << "====================================================" << endl;
    cout<< "Face IdCard Live Detect Four" << endl;
    FaceIdCardLiveDetectFourReq iddetectFourReq(BUCKET);
    iddetectFourReq.SetValidateData(validate);
    iddetectFourReq.SetVideo("ZOE_0171.mp4");
    iddetectFourReq.SetIdCardName("季锦锦");
    iddetectFourReq.SetIdCardNumber("330782198802084329");
    ret = image.FaceIdCardLiveDetectFour(iddetectFourReq);
    cout<<ret<<endl; 

	return 0;
}

