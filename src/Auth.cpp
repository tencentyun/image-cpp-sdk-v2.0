#include "Auth.h"
#include "util/CodecUtil.h"
#include "util/FileUtil.h"
#include "util/true_random.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>

using std::string;
namespace qcloud_image {

std::string Auth::AppSign(uint64_t appid, 
									const std::string& bucket,
									const std::string& secret_id,
									const std::string& secret_key,
									uint64_t expired_time){
    if (secret_id.empty() || secret_key.empty()) {
        return "";
    }

    time_t now = time(NULL);
    static TrueRandom true_random;
    uint64_t rdm = true_random.NextUInt64();
    char plain_text_char[1024];
    unsigned int input_length = snprintf(plain_text_char, sizeof(plain_text_char),
				"a=%llu&b=%s&k=%s&t=%u&e=%u", 
				appid, bucket.c_str(), secret_id.c_str(), now, now+expired_time);

    std::string plain_text(plain_text_char, input_length);
    std::string hmac_digest = CodecUtil::HmacSha1(plain_text, secret_key);
    std::string encode_str = hmac_digest + plain_text;

    return CodecUtil::Base64Encode(encode_str);
}

} // namespace qcloud_image
