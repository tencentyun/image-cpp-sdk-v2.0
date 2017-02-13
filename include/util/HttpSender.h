#ifndef HTTPSENDER_H
#define HTTPSENDER_H
#pragma once

#include <string>
#include <map>
#include <vector>
#include <curl/curl.h>
#include <curl/multi.h>
#include "ImageDefines.h"
#include "json/json.h"

#define MAX_WAIT_MSECS 60       /* Max wait timeout, 30 seconds */

using namespace std;

namespace qcloud_image {
class HttpSender {
private:

    /**
     * @brief 设置HTTP返回值的回调函数
     *
     * @param buffer  返回值暂存的buffer
     * @param size    buffer中每一个对象的大小
     * @param count   对象的个数
     * @param stream  保存返回值的地址
     *
     * @return        返回返回值的字节长度
     */
    static size_t CurlWriter(void* buffer, size_t size, size_t count, void* stream);


    /**
     * @brief 生成一个easy curl对象，并设置一些公共值
     *
     * @param url      url地址
     * @param rsp      保存返回值的std::string对象
     * @param is_post  是否是post请求
     * @param option   用户的一些配置选项，包括超时时间(毫秒)等
     *
     * @return    返回easy_curl对象
     */
    static CURL *CurlEasyHandler(const std::string& url, std::string* rsp,
                                 bool is_post);

    /**
     * @brief 设置easy curl的HTTP头部
     *
     * @param curl_handler    easy_curl类型的头部
     * @param user_headers    用户自定义的http头部map
     *
     * @return 返回curl对象的头部链
     */
    static struct curl_slist* SetCurlHeaders(CURL* curl_handler, const std::map<std::string, std::string>& user_headers);

public:
	/**
	 * @brief				post图片内容列表
	 *
	 * @param url			url地址
	 * @param headers		自定义的HTTP头
	 * @param params		自定义的参数
	 * @param images		图片数据
	 *
	 * @return				server返回应答
	 */
	static string PostImageList(const string& url, 
						 const map<string, string>& headers, 
						 const map<string, string>& params, 
						 const map<string, string>& images);

	/**
	 * @brief				post图片url列表
	 *
	 * @param url			url地址
	 * @param headers		自定义的HTTP头
	 * @param params		自定义的参数
	 * @param urls			图片url列表
	 *
	 * @return				server返回应答
	 */
	static string PostUrlList(const string& url, 
					   const map<string, string>& headers, 
					   const map<string, string>& params, 
					   const vector<string>& urls);

	/**
	 * @brief				post Json结构的数据
	 *
	 * @param url			url地址
	 * @param headers		自定义的HTTP头
	 * @param value		    Json结构的参数
	 *
	 * @return				server返回应答
	 */
	static string PostJsonReq(const string& url, 
					   map<string, string> headers, 
					   const Json::Value& value);

	/**
	 * @brief				post form-data结构的数据
	 *
	 * @param url			url地址
	 * @param headers		自定义的HTTP头
	 * @param value		    HttpForm结构的参数
	 *
	 * @return				server返回应答
	 */
	static string PostFormReq(const string& url, 
					   const map<string, string>& headers, 
					   const HttpForm& form);

    static int64_t GetTimeStampInUs();
};

} // namespace qcloud_image

#endif // HTTPSENDER_H
