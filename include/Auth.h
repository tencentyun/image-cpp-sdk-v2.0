#ifndef AUTH_H
#define AUTH_H

#include <stdint.h>
#include <string>

using std::string;
namespace qcloud_image {

class Auth {
public:
	/// @brief 返回图片处理所用的签名，以下参数含义均可在qcloud官网上
	///        获取帮助：https://www.qcloud.com/doc/product/275/%E6%99%BA%E8%83%BD%E9%89%B4%E9%BB%84#2.2-.E9.89.B4.E6.9D.83
	/// @param appid 项目的appid
	/// @param bucket 图片处理所使用的bucket
	/// @param secret_id 签名秘钥id，可在控制台获得
	/// @param secret_key 签名秘钥，可在控制台获得
	/// @param expired_time 过期时间，单位秒
	/// @return string 签名，如果失败，返回空串
	static std::string AppSign(uint64_t appid, 
									const std::string& bucket,
									const std::string& secret_id,
									const std::string& secret_key,
									uint64_t expired_time);

private:
    Auth() {}
    ~Auth() {}

    Auth(const Auth&);
    Auth& operator=(const Auth&);
};

} // namespace qcloud_image

#endif // AUTH_H
