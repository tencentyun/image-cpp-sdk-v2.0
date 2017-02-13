#include "util/true_random.h"

#include <limits.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

namespace qcloud_image {
TrueRandom::TrueRandom()
{
    m_fd = open("/dev/urandom", O_RDONLY, 0);
    if (m_fd < 0)
    {
        abort();
    }
}

TrueRandom::~TrueRandom()
{
    close(m_fd);
    m_fd = -1;
}

bool TrueRandom::NextBytes(void* buffer, size_t size)
{
    return read(m_fd, buffer, size) == static_cast<int>(size);
}

uint64_t TrueRandom::NextUInt64()
{
    uint64_t bytes = -1;
    NextBytes(&bytes, sizeof(bytes));
    return bytes;
}
} // namespace qcloud_image
