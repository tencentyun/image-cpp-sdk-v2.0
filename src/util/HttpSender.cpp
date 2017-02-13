// Copyright (c) 2016, Tencent Inc.
// All rights reserved.
//
// Author: Wu Cheng <chengwu@tencent.com>
// Created: 03/08/2016
// Description:
#include "util/HttpSender.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <stdint.h>
#include "json/json.h"
#include "ImageParams.h"
#include "request/ImageResult.h"
#include "ImageSysConfig.h"
#include "util/StringUtil.h"
#ifdef __USE_L5
#include "util/l5_endpoint_provider.h"
#endif

namespace qcloud_image {

    size_t HttpSender::CurlWriter(void *buffer, size_t size, size_t count, void *stream) {
        string *pstream = static_cast<string *>(stream);
        (*pstream).append((char *)buffer, size * count);
        return size * count;
    }

    /*
     * 生成一个easy curl对象，并设置一些公共值
     */
    CURL *HttpSender::CurlEasyHandler(const string &url, string *rsp,
                                      bool is_post) {
        CURL *easy_curl = curl_easy_init();

        uint64_t conn_timeout = ImageSysConfig::getConnTimeoutInms();
        uint64_t timeout = ImageSysConfig::getTimeoutInms();
        curl_easy_setopt(easy_curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(easy_curl, CURLOPT_NOSIGNAL, 1);
        // TODO(rabbitliu) 是否需要保护，如最少30s
        curl_easy_setopt(easy_curl, CURLOPT_TIMEOUT_MS, timeout);
        curl_easy_setopt(easy_curl, CURLOPT_CONNECTTIMEOUT_MS, conn_timeout);
        curl_easy_setopt(easy_curl, CURLOPT_SSL_VERIFYHOST, 0);
        curl_easy_setopt(easy_curl, CURLOPT_SSL_VERIFYPEER, 1);

        if (is_post) {
            curl_easy_setopt(easy_curl, CURLOPT_POST, 1);
        }

        curl_easy_setopt(easy_curl, CURLOPT_WRITEFUNCTION, CurlWriter);
        curl_easy_setopt(easy_curl, CURLOPT_WRITEDATA, rsp);

        return easy_curl;
    }

    struct curl_slist* HttpSender::SetCurlHeaders(CURL *curl_handler, const std::map<string, string> &user_headers) {
        struct curl_slist *header_lists = NULL;
        header_lists = curl_slist_append(header_lists, "Accept: */*");
        header_lists = curl_slist_append(header_lists, "Host: service.image.myqcloud.com");
        header_lists = curl_slist_append(header_lists, "Connection: Keep-Alive");
        header_lists = curl_slist_append(header_lists, "User-Agent: image-cpp-sdk");

        std::map<string, string>::const_iterator it = user_headers.begin();
        string header_key, header_value, full_str;
        for (; it != user_headers.end(); ++it) {
            header_key = it->first;
            header_value = it->second;
            full_str = header_key + ": " + header_value;
            header_lists = curl_slist_append(header_lists, full_str.c_str());
        }
        curl_easy_setopt(curl_handler, CURLOPT_HTTPHEADER, header_lists);
        return header_lists;
    }

	int64_t HttpSender::GetTimeStampInUs() {
    // 构造时间
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
	}

	string HttpSender::PostImageList(const string& url, 
									 const map<string, string>& headers, 
									 const map<string, string>& params, 
									 const map<string, string>& images){
		struct curl_httppost *firstitem = NULL;
		struct curl_httppost *lastitem = NULL;
		for(map<string, string>::const_iterator it = params.begin(); 
				it != params.end(); 
				it++){
			curl_formadd(&firstitem, &lastitem,
					CURLFORM_COPYNAME, it->first.c_str(),
					CURLFORM_COPYCONTENTS, it->second.c_str(),
					CURLFORM_END);
		}

		char name[32];
		int cnt = 0;
		for(map<string, string>::const_iterator it = images.begin(); 
				it != images.end(); 
				it++){
				snprintf(name, 32, "image[%d]", cnt++);
			curl_formadd(&firstitem, &lastitem,
					CURLFORM_COPYNAME, name, 
					CURLFORM_BUFFER, it->first.c_str(),
					CURLFORM_BUFFERPTR, it->second.data(), 
					CURLFORM_BUFFERLENGTH, it->second.length(), 
					CURLFORM_END);
		}

		string response = "";
		CURL* image_curl = CurlEasyHandler(url, &response, true);
		curl_slist* header_lists = SetCurlHeaders(image_curl, headers);
		curl_easy_setopt(image_curl, CURLOPT_HTTPPOST, firstitem);

		int64_t start = GetTimeStampInUs();
		CURLcode ret_code = curl_easy_perform(image_curl);
		int64_t time_cost_in_us = GetTimeStampInUs() - start;

		curl_formfree(firstitem);
		curl_slist_free_all(header_lists);
		curl_easy_cleanup(image_curl);

		if (ret_code != CURLE_OK) {
			std::cerr << "PostImageList failed, " << ret_code << std::endl;
			return ImageResult(NETWORK_ERROR, NETWORK_ERROR_DESC).toJsonString();
		}

		return response;
	}
	
	string HttpSender::PostUrlList(const string& url, 
									 const map<string, string>& headers, 
									 const map<string, string>& params, 
									 const vector<string>& urls){
		Json::Value param_json;
		for(map<string, string>::const_iterator it = params.begin(); 
				it != params.end(); 
				it++){
			param_json[it->first] = it->second;
		}
		for(int i = 0; i < urls.size(); i++){
			param_json[PARA_URL_LIST][i] = urls[i];
		}
		Json::FastWriter json_writer;
		string param_str = json_writer.write(param_json);

		string response = "";
		CURL* image_curl = CurlEasyHandler(url, &response, true);
		std::map<string, string> headers_cp = headers;
		headers_cp["Content-Type"] = "application/json";
		curl_slist* header_lists = SetCurlHeaders(image_curl, headers_cp);
		curl_easy_setopt(image_curl, CURLOPT_POSTFIELDS, param_str.c_str());

		int64_t start = GetTimeStampInUs();
		CURLcode ret_code = curl_easy_perform(image_curl);
		int64_t time_cost_in_us = GetTimeStampInUs() - start;

		curl_slist_free_all(header_lists);
		curl_easy_cleanup(image_curl);

		if (ret_code != CURLE_OK) {
			std::cerr << "PostImageList failed, " << ret_code << std::endl;
			return ImageResult(NETWORK_ERROR, NETWORK_ERROR_DESC).toJsonString();
		}

		return response;
	}

    string HttpSender::PostJsonReq(const string& url, 
            map<string, string> headers,
            const Json::Value& value) {

		Json::FastWriter json_writer;
		string param_str = json_writer.write(value);

		string response = "";
		CURL* image_curl = CurlEasyHandler(url, &response, true);
		headers["Content-Type"] = "application/json";
		curl_slist* header_lists = SetCurlHeaders(image_curl, headers);
		curl_easy_setopt(image_curl, CURLOPT_POSTFIELDS, param_str.c_str());

		//int64_t start = GetTimeStampInUs();
		CURLcode ret_code = curl_easy_perform(image_curl);
		//int64_t time_cost_in_us = GetTimeStampInUs() - start;

		curl_slist_free_all(header_lists);
		curl_easy_cleanup(image_curl);

		if (ret_code != CURLE_OK) {
			std::cerr << "PostJsonReq failed! url[" << url << "] ret[" << ret_code << "]" << std::endl;
			return ImageResult(NETWORK_ERROR, NETWORK_ERROR_DESC).toJsonString();
		}

		return response;
	}

	string HttpSender::PostFormReq(const string& url, 
					   const map<string, string>& headers, 
					   const HttpForm& form) {

		struct curl_httppost *firstitem = NULL;
		struct curl_httppost *lastitem = NULL;
		for (HttpFormConstIter it = form.begin(); it != form.end(); ++it) {
            if (it->second.second) {
                curl_formadd(&firstitem, &lastitem,
                        CURLFORM_COPYNAME, it->first.c_str(), 
                        CURLFORM_BUFFER, it->first.c_str(),
                        CURLFORM_BUFFERPTR, it->second.first.data(), 
                        CURLFORM_BUFFERLENGTH, it->second.first.length(), 
                        CURLFORM_END);
            } else {
                curl_formadd(&firstitem, &lastitem,
                        CURLFORM_COPYNAME, it->first.c_str(),
                        CURLFORM_COPYCONTENTS, it->second.first.c_str(),
                        CURLFORM_END);
            }
		}

		string response = "";
		CURL* image_curl = CurlEasyHandler(url, &response, true);
		curl_slist* header_lists = SetCurlHeaders(image_curl, headers);
		curl_easy_setopt(image_curl, CURLOPT_HTTPPOST, firstitem);

		//int64_t start = GetTimeStampInUs();
		CURLcode ret_code = curl_easy_perform(image_curl);
		//int64_t time_cost_in_us = GetTimeStampInUs() - start;

		curl_formfree(firstitem);
		curl_slist_free_all(header_lists);
		curl_easy_cleanup(image_curl);

		if (ret_code != CURLE_OK) {
			std::cerr << "PostFormReq failed! url[" << url << "] ret[" << ret_code << "]" << std::endl;
			return ImageResult(NETWORK_ERROR, NETWORK_ERROR_DESC).toJsonString();
		}

		return response;
    }
}
