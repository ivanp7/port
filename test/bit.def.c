#include "test.h"

#include "port/types.typ.h"
#include "port/bit.def.h"

TEST(PORT_NUM_BITS)
{
    ASSERT_EQ(PORT_NUM_BITS(port_uint8_t), 8, port_uint32_t, "%u");
    ASSERT_EQ(PORT_NUM_BITS(port_sint8_t), 8, port_uint32_t, "%u");
    ASSERT_EQ(PORT_NUM_BITS(port_uint16_t), 16, port_uint32_t, "%u");
    ASSERT_EQ(PORT_NUM_BITS(port_sint16_t), 16, port_uint32_t, "%u");
    ASSERT_EQ(PORT_NUM_BITS(port_uint32_t), 32, port_uint32_t, "%u");
    ASSERT_EQ(PORT_NUM_BITS(port_sint32_t), 32, port_uint32_t, "%u");
    ASSERT_EQ(PORT_NUM_BITS(port_uint64_t), 64, port_uint32_t, "%u");
    ASSERT_EQ(PORT_NUM_BITS(port_sint64_t), 64, port_uint32_t, "%u");
    ASSERT_EQ(PORT_NUM_BITS(port_float32_t), 32, port_uint32_t, "%u");
    ASSERT_EQ(PORT_NUM_BITS(port_float64_t), 64, port_uint32_t, "%u");

    ASSERT_EQ(PORT_NUM_BITS(port_uint_quarter_t), 8, port_uint32_t, "%u");
    ASSERT_EQ(PORT_NUM_BITS(port_sint_quarter_t), 8, port_uint32_t, "%u");
    ASSERT_EQ(PORT_NUM_BITS(port_uint_half_t), 16, port_uint32_t, "%u");
    ASSERT_EQ(PORT_NUM_BITS(port_sint_half_t), 16, port_uint32_t, "%u");
    ASSERT_EQ(PORT_NUM_BITS(port_uint_single_t), 32, port_uint32_t, "%u");
    ASSERT_EQ(PORT_NUM_BITS(port_sint_single_t), 32, port_uint32_t, "%u");
    ASSERT_EQ(PORT_NUM_BITS(port_uint_double_t), 64, port_uint32_t, "%u");
    ASSERT_EQ(PORT_NUM_BITS(port_sint_double_t), 64, port_uint32_t, "%u");
    ASSERT_EQ(PORT_NUM_BITS(port_float_single_t), 32, port_uint32_t, "%u");
    ASSERT_EQ(PORT_NUM_BITS(port_float_double_t), 64, port_uint32_t, "%u");
}

TEST(PORT_INT_UNITS)
{
    ASSERT_EQ(PORT_INT_UNITS(port_uint32_t, 0, 0), 0, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_UNITS(port_uint32_t, 1, 0), 1, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_UNITS(port_uint32_t, 2, 0), 2, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_UNITS(port_uint32_t, 3, 0), 3, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_UNITS(port_uint32_t, 4, 0), 4, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_UNITS(port_uint32_t, 0, 1), 0, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_UNITS(port_uint32_t, 1, 1), 1, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_UNITS(port_uint32_t, 2, 1), 1, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_UNITS(port_uint32_t, 3, 1), 2, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_UNITS(port_uint32_t, 4, 1), 2, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_UNITS(port_uint32_t, 5, 1), 3, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_UNITS(port_uint32_t, 6, 1), 3, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_UNITS(port_uint32_t, 7, 1), 4, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_UNITS(port_uint32_t, 8, 1), 4, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_UNITS(port_uint32_t, 0, 2), 0, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_UNITS(port_uint32_t, 1, 2), 1, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_UNITS(port_uint32_t, 2, 2), 1, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_UNITS(port_uint32_t, 3, 2), 1, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_UNITS(port_uint32_t, 4, 2), 1, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_UNITS(port_uint32_t, 5, 2), 2, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_UNITS(port_uint32_t, 6, 2), 2, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_UNITS(port_uint32_t, 7, 2), 2, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_UNITS(port_uint32_t, 8, 2), 2, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_UNITS(port_uint32_t, 9, 2), 3, port_uint32_t, "%u");
}

TEST(PORT_INT_ROUND)
{
    ASSERT_EQ(PORT_INT_ROUND(port_uint32_t, 0, 0), 0, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_ROUND(port_uint32_t, 1, 0), 1, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_ROUND(port_uint32_t, 2, 0), 2, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_ROUND(port_uint32_t, 3, 0), 3, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_ROUND(port_uint32_t, 4, 0), 4, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_ROUND(port_uint32_t, 0, 1), 0, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_ROUND(port_uint32_t, 1, 1), 2, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_ROUND(port_uint32_t, 2, 1), 2, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_ROUND(port_uint32_t, 3, 1), 4, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_ROUND(port_uint32_t, 4, 1), 4, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_ROUND(port_uint32_t, 5, 1), 6, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_ROUND(port_uint32_t, 6, 1), 6, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_ROUND(port_uint32_t, 7, 1), 8, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_ROUND(port_uint32_t, 8, 1), 8, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_ROUND(port_uint32_t, 0, 2), 0, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_ROUND(port_uint32_t, 1, 2), 4, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_ROUND(port_uint32_t, 2, 2), 4, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_ROUND(port_uint32_t, 3, 2), 4, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_ROUND(port_uint32_t, 4, 2), 4, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_ROUND(port_uint32_t, 5, 2), 8, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_ROUND(port_uint32_t, 6, 2), 8, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_ROUND(port_uint32_t, 7, 2), 8, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_ROUND(port_uint32_t, 8, 2), 8, port_uint32_t, "%u");
    ASSERT_EQ(PORT_INT_ROUND(port_uint32_t, 9, 2), 12, port_uint32_t, "%u");
}

TEST(PORT_BYTE)
{
    ASSERT_EQ(PORT_BYTE(0, 0, 0, 0, 0, 0, 0, 0), 0, port_uint8_t, "%u");
    ASSERT_EQ(PORT_BYTE(1, 0, 0, 0, 1, 0, 0, 1), 137, port_uint8_t, "%u");
    ASSERT_EQ(PORT_BYTE(1, 1, 1, 1, 1, 1, 1, 1), 255, port_uint8_t, "%u");
}

TEST(PORT_CONCAT_BITS)
{
    ASSERT_EQ(PORT_CONCAT_BITS(port_uint16_t, 0xA, 8, 0xBC), 0xABC, port_uint16_t, "%X");
    ASSERT_EQ(PORT_CONCAT_BITS(port_uint16_t, 0xA, 12, 0xBC), 0xA0BC, port_uint16_t, "%X");
}

TEST(PORT_EXTRACT_BITS)
{
    ASSERT_EQ(PORT_EXTRACT_BITS(port_uint16_t, 0xABCD, 0, 4), 0xD, port_uint16_t, "%X");
    ASSERT_EQ(PORT_EXTRACT_BITS(port_uint16_t, 0xABCD, 4, 4), 0xC, port_uint16_t, "%X");
    ASSERT_EQ(PORT_EXTRACT_BITS(port_uint16_t, 0xABCD, 8, 4), 0xB, port_uint16_t, "%X");
    ASSERT_EQ(PORT_EXTRACT_BITS(port_uint16_t, 0xABCD, 12, 4), 0xA, port_uint16_t, "%X");
    ASSERT_EQ(PORT_EXTRACT_BITS(port_uint16_t, 0xABCD, 12, 2), 0x2, port_uint16_t, "%X");
    ASSERT_EQ(PORT_EXTRACT_BITS(port_uint16_t, 0xABCD, 13, 2), 0x1, port_uint16_t, "%X");
}

TEST(PORT_BIT)
{
    ASSERT_EQ(PORT_BIT8(0), 0x1, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_BIT8(1), 0x2, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_BIT8(2), 0x4, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_BIT8(7), 0x80, port_uint64_t, "%lX");

    ASSERT_EQ(PORT_BIT16(0), 0x1, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_BIT16(1), 0x2, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_BIT16(2), 0x4, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_BIT16(15), 0x8000, port_uint64_t, "%lX");

    ASSERT_EQ(PORT_BIT32(0), 0x1, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_BIT32(1), 0x2, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_BIT32(2), 0x4, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_BIT32(16), 0x00010000, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_BIT32(31), 0x80000000, port_uint64_t, "%lX");

    ASSERT_EQ(PORT_BIT64(0), 0x1, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_BIT64(1), 0x2, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_BIT64(2), 0x4, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_BIT64(16), 0x00010000, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_BIT64(31), 0x80000000, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_BIT64(63), 0x8000000000000000ull, port_uint64_t, "%lX");
}

TEST(PORT_ZMASK)
{
    ASSERT_EQ(PORT_ZMASK8(0), 0, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_ZMASK8(1), 0x1, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_ZMASK8(2), 0x3, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_ZMASK8(7), 0x7F, port_uint64_t, "%lX");

    ASSERT_EQ(PORT_ZMASK16(0), 0, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_ZMASK16(1), 0x1, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_ZMASK16(2), 0x3, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_ZMASK16(15), 0x7FFF, port_uint64_t, "%lX");

    ASSERT_EQ(PORT_ZMASK32(0), 0, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_ZMASK32(1), 0x1, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_ZMASK32(2), 0x3, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_ZMASK32(16), 0x0000FFFF, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_ZMASK32(31), 0x7FFFFFFF, port_uint64_t, "%lX");

    ASSERT_EQ(PORT_ZMASK64(0), 0, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_ZMASK64(1), 0x1, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_ZMASK64(2), 0x3, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_ZMASK64(16), 0x0000FFFF, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_ZMASK64(31), 0x7FFFFFFF, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_ZMASK64(32), 0xFFFFFFFF, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_ZMASK64(33), 0x1FFFFFFFF, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_ZMASK64(63), 0x7FFFFFFFFFFFFFFFull, port_uint64_t, "%lX");
}

TEST(PORT_NZMASK)
{
    ASSERT_EQ(PORT_NZMASK8(1), 0x1, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_NZMASK8(2), 0x3, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_NZMASK8(7), 0x7F, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_NZMASK8(8), 0xFF, port_uint64_t, "%lX");

    ASSERT_EQ(PORT_NZMASK16(1), 0x1, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_NZMASK16(2), 0x3, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_NZMASK16(15), 0x7FFF, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_NZMASK16(16), 0xFFFF, port_uint64_t, "%lX");

    ASSERT_EQ(PORT_NZMASK32(1), 0x1, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_NZMASK32(2), 0x3, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_NZMASK32(16), 0x0000FFFF, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_NZMASK32(31), 0x7FFFFFFF, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_NZMASK32(32), 0xFFFFFFFF, port_uint64_t, "%lX");

    ASSERT_EQ(PORT_NZMASK64(1), 0x1, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_NZMASK64(2), 0x3, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_NZMASK64(16), 0x0000FFFF, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_NZMASK64(31), 0x7FFFFFFF, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_NZMASK64(32), 0xFFFFFFFF, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_NZMASK64(33), 0x1FFFFFFFF, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_NZMASK64(63), 0x7FFFFFFFFFFFFFFFull, port_uint64_t, "%lX");
    ASSERT_EQ(PORT_NZMASK64(64), 0xFFFFFFFFFFFFFFFFull, port_uint64_t, "%lX");
}

TEST(PORT_UPSAMPLE)
{
    ASSERT_EQ(PORT_UPSAMPLE8(0x12, 0xAB), 0x12AB, port_uint16_t, "%X");
    ASSERT_EQ(PORT_UPSAMPLE16(0x1234, 0xABCD), 0x1234ABCDul, port_uint32_t, "%X");
    ASSERT_EQ(PORT_UPSAMPLE32(0x12345678ul, 0xABCDEF90ul), 0x12345678ABCDEF90ull, port_uint64_t, "%lX");
}

TEST(PORT_POPCOUNT)
{
    ASSERT_EQ(PORT_POPCOUNT8(0x00), 0, port_uint8_t, "%u");
    ASSERT_EQ(PORT_POPCOUNT8(0xAA), 4, port_uint8_t, "%u");
    ASSERT_EQ(PORT_POPCOUNT8(0xFF), 8, port_uint8_t, "%u");
    ASSERT_EQ(PORT_POPCOUNT8(0xFFFF), 8, port_uint8_t, "%u");

    ASSERT_EQ(PORT_POPCOUNT16(0x0000), 0, port_uint8_t, "%u");
    ASSERT_EQ(PORT_POPCOUNT16(0xAA55), 8, port_uint8_t, "%u");
    ASSERT_EQ(PORT_POPCOUNT16(0xFFFF), 16, port_uint8_t, "%u");
    ASSERT_EQ(PORT_POPCOUNT16(0xFFFFFFFF), 16, port_uint8_t, "%u");

    ASSERT_EQ(PORT_POPCOUNT32(0x00000000ul), 0, port_uint8_t, "%u");
    ASSERT_EQ(PORT_POPCOUNT32(0xAA55AA55ul), 16, port_uint8_t, "%u");
    ASSERT_EQ(PORT_POPCOUNT32(0xFFFFFFFFul), 32, port_uint8_t, "%u");
    ASSERT_EQ(PORT_POPCOUNT32(0xFFFFFFFFFFFFFFFFul), 32, port_uint8_t, "%u");

    ASSERT_EQ(PORT_POPCOUNT64(0x0000000000000000ull), 0, port_uint8_t, "%u");
    ASSERT_EQ(PORT_POPCOUNT64(0xAA55AA55AA55AA55ull), 32, port_uint8_t, "%u");
    ASSERT_EQ(PORT_POPCOUNT64(0xFFFFFFFFFFFFFFFFull), 64, port_uint8_t, "%u");
}

TEST(PORT_CLZ)
{
    ASSERT_EQ(PORT_CLZ8(0), 8, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ8(0x1), 7, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ8(0x2), 6, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ8(0x3), 6, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ8(0x4), 5, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ8(0x7F), 1, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ8(0x80), 0, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ8(0xFF), 0, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ8(0xFFFF), 0, port_uint32_t, "%u");

    ASSERT_EQ(PORT_CLZ16(0), 16, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ16(0x1), 15, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ16(0x2), 14, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ16(0x3), 14, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ16(0x4), 13, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ16(0x7F), 9, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ16(0x80), 8, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ16(0xFF), 8, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ16(0x8000), 0, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ16(0xFFFF), 0, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ16(0xFFFFFFFF), 0, port_uint32_t, "%u");

    ASSERT_EQ(PORT_CLZ32(0), 32, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ32(0x1), 31, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ32(0x2), 30, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ32(0x3), 30, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ32(0x4), 29, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ32(0x7FFF), 17, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ32(0x8000), 16, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ32(0xFFFF), 16, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ32(0x80000000), 0, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ32(0xFFFFFFFF), 0, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ32(0xFFFFFFFFFFFFFFFFull), 0, port_uint32_t, "%u");

    ASSERT_EQ(PORT_CLZ64(0), 64, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ64(0x1), 63, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ64(0x2), 62, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ64(0x3), 62, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ64(0x4), 61, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ64(0x7FFFFFFF), 33, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ64(0x80000000), 32, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ64(0xFFFFFFFF), 32, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ64(0x8000000000000000ull), 0, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CLZ64(0xFFFFFFFFFFFFFFFFull), 0, port_uint32_t, "%u");
}

TEST(PORT_CTZ)
{
    ASSERT_EQ(PORT_CTZ8(0), 8, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ8(0x1), 0, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ8(0x2), 1, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ8(0x3), 0, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ8(0x4), 2, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ8(0x7F), 0, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ8(0x80), 7, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ8(0xFF), 0, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ8(0x8000), 8, port_uint32_t, "%u");

    ASSERT_EQ(PORT_CTZ16(0), 16, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ16(0x1), 0, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ16(0x2), 1, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ16(0x3), 0, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ16(0x4), 2, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ16(0x7F), 0, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ16(0x80), 7, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ16(0xFF), 0, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ16(0x8000), 15, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ16(0x80000000), 16, port_uint32_t, "%u");

    ASSERT_EQ(PORT_CTZ32(0), 32, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ32(0x1), 0, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ32(0x2), 1, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ32(0x3), 0, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ32(0x4), 2, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ32(0x7F), 0, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ32(0x80), 7, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ32(0xFF), 0, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ32(0x8000), 15, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ32(0x80000000), 31, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ32(0x8000000000000000ull), 32, port_uint32_t, "%u");

    ASSERT_EQ(PORT_CTZ64(0), 64, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ64(0x1), 0, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ64(0x2), 1, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ64(0x3), 0, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ64(0x4), 2, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ64(0x7F), 0, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ64(0x80), 7, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ64(0xFF), 0, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ64(0x8000), 15, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ64(0x80000000), 31, port_uint32_t, "%u");
    ASSERT_EQ(PORT_CTZ64(0x8000000000000000ull), 63, port_uint32_t, "%u");
}

