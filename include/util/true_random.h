#ifndef _TRUE_RANDOM_H
#define _TRUE_RANDOM_H
#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

namespace qcloud_image {
/// true random generator
class TrueRandom {
public:
    TrueRandom();
    ~TrueRandom();

    /// return random integer in range [0, UINT64_MAX]
    uint64_t NextUInt64();

    /// generate random bytes
    bool NextBytes(void* buffer, size_t size);

private:
    int m_fd;               /// fd for /dev/urandom
};
} // namespace qcloud_image
#endif // TRUE_RANDOM_H
