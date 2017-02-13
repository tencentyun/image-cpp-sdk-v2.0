#ifndef CODEC_UTIL_H
#define CODEC_UTIL_H

#include <string>
#include <stdint.h>
#include "json/json.h"
using std::string;
namespace qcloud_image {

class CodecUtil {
public:

    /**
     * @brief ���ַ�xת��ʮ������ (x��ֵ[0, 15])
     *
     * @param x
     *
     * @return ʮ�������ַ�
     */
    static unsigned char ToHex(const unsigned char& x);


    /**
     * @brief ���ַ�������URL����
     *
     * @param str   ��������ַ���
     *
     * @return  ����URL������ַ���
     */
    static std::string UrlEncode(const std::string& str);


    /**
     * @brief ���ַ�������base64����
     *
     * @param plainText  ��������ַ���
     *
     * @return �������ַ���
     */
    static std::string Base64Encode(const std::string& plainText);

    /**
     * @brief ��ȡhmacSha1ֵ
     *
     * @param plainText  ����
     * @param key        ��Կ
     *
     * @return ��ȡ��hmacsha1ֵ
     */
    static std::string HmacSha1(const std::string& plainText,
                           const std::string &key);
    /**
     * @brief ��ȡ�ļ���sha1ֵ
     *
     * @param localFilePath  �����ļ�·��
     *
     * @return �ļ���sha1ֵ
     */
    static std::string GetFileSha1(const std::string& localFilePath);

    static std::string GetFileSha1(const char* buffer, size_t buff_len);

    static int conv_file_to_upload_parts(const string &filepath, uint64_t slice_size, string &upload_parts, string& sha1);

};

}
#endif 
