#ifndef _IMAGE_SYS_CONFIG_H_
#define _IMAGE_SYS_CONFIG_H_
#include <stdint.h>
#include <pthread.h>
#include "curl/curl.h"

namespace qcloud_image{

#define DEFAULT_SIGN_EXPIRED_TIME	300
#define DEFAULT_CONN_TIMEOUT_MS		1000
#define DEFAULT_TIMEOUT_TIMEOUT_MS	10*1000	

class ImageSysConfig {
public:
    static void setAuthExpiredTime(uint64_t time) { _g_auth_expire_time = time; }     
    static void setConnTimeoutInms(uint64_t time) { _g_conn_timeout = time; }
    static void setTimeoutInms(uint64_t time) { _g_timeout = time; }
    static uint64_t getAuthExpiredTime() { return _g_auth_expire_time; }
    static uint64_t getConnTimeoutInms() { return _g_conn_timeout; }
    static uint64_t getTimeoutInms() { return _g_timeout; }
private:
    //签名超时时间
    static uint64_t _g_auth_expire_time;
    //连接超时时间(毫秒)
    static uint64_t _g_conn_timeout;
    //请求超时时间(毫秒)
    static uint64_t _g_timeout;
};

}

#endif
