#include "ImageSysConfig.h"
#include "ImageDefines.h"

namespace qcloud_image {
uint64_t ImageSysConfig::_g_auth_expire_time = DEFAULT_SIGN_EXPIRED_TIME;
uint64_t ImageSysConfig::_g_conn_timeout = DEFAULT_CONN_TIMEOUT_MS;
uint64_t ImageSysConfig::_g_timeout = DEFAULT_TIMEOUT_TIMEOUT_MS;
}
