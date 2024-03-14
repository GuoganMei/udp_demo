/* related header files */
#include "basic_math.hpp"

namespace basic_math
{
/**
 * @brief 32-bit CRC function
 * @param[in] src data address
 * @param[in] len data length
 * @return 32-bit CRC value
 */
uint32_t crc32Core(volatile uint8_t *src, uint32_t len)
{
    auto *ptr = (uint32_t *)src;
    uint32_t xbit = 0;
    uint32_t data = 0;
    uint32_t CRC32 = 0xFFFFFFFF;
    const uint32_t dwPolynomial = 0x04c11db7;
    for (uint32_t i = 0; i < len; i++)
    {
        xbit = 1 << 31;
        data = ptr[i];
        for (uint32_t bits = 0; bits < 32; bits++)
        {
            if (CRC32 & 0x80000000)
            {
                CRC32 <<= 1;
                CRC32 ^= dwPolynomial;
            }
            else
                CRC32 <<= 1;
            if (data & xbit)
                CRC32 ^= dwPolynomial;
            xbit >>= 1;
        }
    }
    return CRC32;
}

} // namespace basic_math
