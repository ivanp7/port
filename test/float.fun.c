#include "test.h"

#include "port/float.fun.h"
#include "port/constants.def.h"
#include "port/types.def.h"
#include "port/vector.def.h"

#include <tgmath.h>

TEST(port_float32_clamp)
{
    ASSERT_EQ(port_float32_clamp(0.5f, 0.0f, 1.0f), 0.5f, port_float32_t, "%g");
    ASSERT_EQ(port_float32_clamp(-0.5f, 0.0f, 1.0f), 0.0f, port_float32_t, "%g");
    ASSERT_EQ(port_float32_clamp(1.5f, 0.0f, 1.0f), 1.0f, port_float32_t, "%g");
    ASSERT_EQ(port_float32_clamp(PORT_M_INFINITY, 0.0f, 1.0f), 1.0f, port_float32_t, "%g");
    ASSERT_EQ(port_float32_clamp(-1.0f, 0.0f, PORT_M_INFINITY), 0.0f, port_float32_t, "%g");
    ASSERT_EQ(port_float32_clamp(1.0f, 0.0f, PORT_M_INFINITY), 1.0f, port_float32_t, "%g");
    ASSERT_EQ(port_float32_clamp(PORT_M_INFINITY, 0.0f, PORT_M_INFINITY), PORT_M_INFINITY, port_float32_t, "%g");
    ASSERT_EQ(port_float32_clamp(-PORT_M_INFINITY, 0.0f, PORT_M_INFINITY), 0.0f, port_float32_t, "%g");
}

TEST(port_float64_clamp)
{
    ASSERT_EQ(port_float64_clamp(0.5, 0.0, 1.0), 0.5, port_float64_t, "%g");
    ASSERT_EQ(port_float64_clamp(-0.5, 0.0, 1.0), 0.0, port_float64_t, "%g");
    ASSERT_EQ(port_float64_clamp(1.5, 0.0, 1.0), 1.0, port_float64_t, "%g");
    ASSERT_EQ(port_float64_clamp(PORT_M_INFINITY, 0.0, 1.0), 1.0, port_float64_t, "%g");
    ASSERT_EQ(port_float64_clamp(-1.0, 0.0, PORT_M_INFINITY), 0.0, port_float64_t, "%g");
    ASSERT_EQ(port_float64_clamp(1.0, 0.0, PORT_M_INFINITY), 1.0, port_float64_t, "%g");
    ASSERT_EQ(port_float64_clamp(PORT_M_INFINITY, 0.0, PORT_M_INFINITY), PORT_M_INFINITY, port_float64_t, "%g");
    ASSERT_EQ(port_float64_clamp(-PORT_M_INFINITY, 0.0, PORT_M_INFINITY), 0.0, port_float64_t, "%g");
}

TEST(port_float32_ulp_distance)
{
    ASSERT_EQ(port_float32_ulp_distance(0.0f, 0.0f), 0, port_uint32_t, "%u");
    ASSERT_EQ(port_float32_ulp_distance(0.0f, copysign(0.0f, -1.0f)), 0, port_uint32_t, "%u");
    ASSERT_EQ(port_float32_ulp_distance(1.0f, 1.0f), 0, port_uint32_t, "%u");
    ASSERT_EQ(port_float32_ulp_distance(-2.5f, -2.5f), 0, port_uint32_t, "%u");
    ASSERT_EQ(port_float32_ulp_distance(2.0f, 1.0f), 8388608, port_uint32_t, "%u");
    ASSERT_EQ(port_float32_ulp_distance(-2.0f, -1.0f), 8388608, port_uint32_t, "%u");
    ASSERT_EQ(port_float32_ulp_distance(2.0f, -1.0f), 2139095040, port_uint32_t, "%u");
    ASSERT_EQ(port_float32_ulp_distance(-2.0f, 1.0f), 2139095040, port_uint32_t, "%u");
    ASSERT_EQ(port_float32_ulp_distance(0.0f, nextafter(0.0f, +PORT_M_INFINITY)), 1, port_uint32_t, "%u");
    ASSERT_EQ(port_float32_ulp_distance(0.0f, nextafter(0.0f, -PORT_M_INFINITY)), 1, port_uint32_t, "%u");
    ASSERT_EQ(port_float32_ulp_distance(1.0f, nextafter(1.0f, +PORT_M_INFINITY)), 1, port_uint32_t, "%u");
    ASSERT_EQ(port_float32_ulp_distance(1.0f, nextafter(1.0f, -PORT_M_INFINITY)), 1, port_uint32_t, "%u");
    ASSERT_EQ(port_float32_ulp_distance(-1.0f, nextafter(-1.0f, +PORT_M_INFINITY)), 1, port_uint32_t, "%u");
    ASSERT_EQ(port_float32_ulp_distance(-1.0f, nextafter(-1.0f, -PORT_M_INFINITY)), 1, port_uint32_t, "%u");
    ASSERT_EQ(port_float32_ulp_distance(1.0f, PORT_M_INFINITY), (port_uint32_t)-1, port_uint32_t, "%u");
    ASSERT_EQ(port_float32_ulp_distance(PORT_M_INFINITY, -1.0f), (port_uint32_t)-1, port_uint32_t, "%u");
    ASSERT_EQ(port_float32_ulp_distance(-1.0f, PORT_M_NAN), (port_uint32_t)-1, port_uint32_t, "%u");
    ASSERT_EQ(port_float32_ulp_distance(PORT_M_NAN, 1.0f), (port_uint32_t)-1, port_uint32_t, "%u");
    ASSERT_EQ(port_float32_ulp_distance(PORT_M_INFINITY, PORT_M_INFINITY), (port_uint32_t)-1, port_uint32_t, "%u");
    ASSERT_EQ(port_float32_ulp_distance(PORT_M_NAN, PORT_M_NAN), (port_uint32_t)-1, port_uint32_t, "%u");
}

TEST(port_float64_ulp_distance)
{
    ASSERT_EQ(port_float64_ulp_distance(0.0, 0.0), 0, port_uint64_t, "%lu");
    ASSERT_EQ(port_float64_ulp_distance(0.0, copysign(0.0, -1.0)), 0, port_uint64_t, "%lu");
    ASSERT_EQ(port_float64_ulp_distance(1.0, 1.0), 0, port_uint64_t, "%lu");
    ASSERT_EQ(port_float64_ulp_distance(-2.5, -2.5), 0, port_uint64_t, "%lu");
    ASSERT_EQ(port_float64_ulp_distance(2.0, 1.0), 4503599627370496, port_uint64_t, "%lu");
    ASSERT_EQ(port_float64_ulp_distance(-2.0, -1.0), 4503599627370496, port_uint64_t, "%lu");
    ASSERT_EQ(port_float64_ulp_distance(2.0, -1.0), 9218868437227405312, port_uint64_t, "%lu");
    ASSERT_EQ(port_float64_ulp_distance(-2.0, 1.0), 9218868437227405312, port_uint64_t, "%lu");
    ASSERT_EQ(port_float64_ulp_distance(0.0, nextafter(0.0, +PORT_M_INFINITY)), 1, port_uint64_t, "%lu");
    ASSERT_EQ(port_float64_ulp_distance(0.0, nextafter(0.0, -PORT_M_INFINITY)), 1, port_uint64_t, "%lu");
    ASSERT_EQ(port_float64_ulp_distance(1.0, nextafter(1.0, +PORT_M_INFINITY)), 1, port_uint64_t, "%lu");
    ASSERT_EQ(port_float64_ulp_distance(1.0, nextafter(1.0, -PORT_M_INFINITY)), 1, port_uint64_t, "%lu");
    ASSERT_EQ(port_float64_ulp_distance(-1.0, nextafter(-1.0, +PORT_M_INFINITY)), 1, port_uint64_t, "%lu");
    ASSERT_EQ(port_float64_ulp_distance(-1.0, nextafter(-1.0, -PORT_M_INFINITY)), 1, port_uint64_t, "%lu");
    ASSERT_EQ(port_float64_ulp_distance(1.0, PORT_M_INFINITY), (port_uint64_t)-1, port_uint64_t, "%lu");
    ASSERT_EQ(port_float64_ulp_distance(PORT_M_INFINITY, -1.0), (port_uint64_t)-1, port_uint64_t, "%lu");
    ASSERT_EQ(port_float64_ulp_distance(-1.0, PORT_M_NAN), (port_uint64_t)-1, port_uint64_t, "%lu");
    ASSERT_EQ(port_float64_ulp_distance(PORT_M_NAN, 1.0), (port_uint64_t)-1, port_uint64_t, "%lu");
    ASSERT_EQ(port_float64_ulp_distance(PORT_M_INFINITY, PORT_M_INFINITY), (port_uint64_t)-1, port_uint64_t, "%lu");
    ASSERT_EQ(port_float64_ulp_distance(PORT_M_NAN, PORT_M_NAN), (port_uint64_t)-1, port_uint64_t, "%lu");
}

TEST(port_float32_equal)
{
#define TOLERANCE  16

    ASSERT_TRUE(port_float32_equal(PORT_FLOAT32(0.0), PORT_FLOAT32(0.0), TOLERANCE));
    ASSERT_TRUE(port_float32_equal(-TOLERANCE*PORT_FLOAT32_EPS, PORT_FLOAT32(0.0), TOLERANCE));
    ASSERT_TRUE(port_float32_equal(+TOLERANCE*PORT_FLOAT32_EPS, PORT_FLOAT32(0.0), TOLERANCE));
    ASSERT_FALSE(port_float32_equal(-(TOLERANCE+1)*PORT_FLOAT32_EPS, PORT_FLOAT32(0.0), TOLERANCE));
    ASSERT_FALSE(port_float32_equal(+(TOLERANCE+1)*PORT_FLOAT32_EPS, PORT_FLOAT32(0.0), TOLERANCE));
    ASSERT_FALSE(port_float32_equal(PORT_M_NAN, PORT_FLOAT32(0.0), TOLERANCE));
    ASSERT_FALSE(port_float32_equal(PORT_M_INFINITY, PORT_FLOAT32(0.0), TOLERANCE));
    ASSERT_FALSE(port_float32_equal(-PORT_M_INFINITY, PORT_FLOAT32(0.0), TOLERANCE));

    ASSERT_TRUE(port_float32_equal(PORT_FLOAT32(1.0), PORT_FLOAT32(1.0), TOLERANCE));
    ASSERT_TRUE(port_float32_equal(PORT_FLOAT32(1.0)+TOLERANCE*PORT_FLOAT32_EPS, PORT_FLOAT32(1.0), TOLERANCE));
    ASSERT_TRUE(port_float32_equal(PORT_FLOAT32(1.0)-TOLERANCE*PORT_FLOAT32_EPS, PORT_FLOAT32(1.0), TOLERANCE));
    ASSERT_FALSE(port_float32_equal(PORT_FLOAT32(1.0)+(TOLERANCE+1)*PORT_FLOAT32_EPS, PORT_FLOAT32(1.0), TOLERANCE));
    ASSERT_FALSE(port_float32_equal(PORT_FLOAT32(1.0)-(TOLERANCE+1)*PORT_FLOAT32_EPS, PORT_FLOAT32(1.0), TOLERANCE));
    ASSERT_FALSE(port_float32_equal(PORT_M_NAN, PORT_FLOAT32(1.0), TOLERANCE));
    ASSERT_FALSE(port_float32_equal(PORT_M_INFINITY, PORT_FLOAT32(1.0), TOLERANCE));
    ASSERT_FALSE(port_float32_equal(-PORT_M_INFINITY, PORT_FLOAT32(1.0), TOLERANCE));

    ASSERT_TRUE(port_float32_equal(PORT_FLOAT32(768.0), PORT_FLOAT32(768.0), TOLERANCE));
    ASSERT_TRUE(port_float32_equal(PORT_FLOAT32(768.0), PORT_FLOAT32(768.0) + 512*TOLERANCE*PORT_FLOAT32_EPS, TOLERANCE));
    ASSERT_TRUE(port_float32_equal(PORT_FLOAT32(768.0), PORT_FLOAT32(768.0) - 512*TOLERANCE*PORT_FLOAT32_EPS, TOLERANCE));
    ASSERT_FALSE(port_float32_equal(PORT_FLOAT32(768.0), PORT_FLOAT32(768.0) + 512*(TOLERANCE+1)*PORT_FLOAT32_EPS, TOLERANCE));
    ASSERT_FALSE(port_float32_equal(PORT_FLOAT32(768.0), PORT_FLOAT32(768.0) - 512*(TOLERANCE+1)*PORT_FLOAT32_EPS, TOLERANCE));
    ASSERT_FALSE(port_float32_equal(PORT_FLOAT32(768.0), PORT_M_NAN, TOLERANCE));
    ASSERT_FALSE(port_float32_equal(PORT_FLOAT32(768.0), PORT_M_INFINITY, TOLERANCE));
    ASSERT_FALSE(port_float32_equal(PORT_M_NAN, PORT_M_NAN, TOLERANCE));
    ASSERT_TRUE(port_float32_equal(PORT_M_INFINITY, PORT_M_INFINITY, TOLERANCE));
    ASSERT_FALSE(port_float32_equal(-PORT_M_INFINITY, PORT_M_INFINITY, TOLERANCE));
    ASSERT_FALSE(port_float32_equal(PORT_M_NAN, PORT_M_INFINITY, TOLERANCE));

    ASSERT_FALSE(port_float32_equal(PORT_FLOAT32(1.0), PORT_FLOAT32(1.0) + PORT_FLOAT32_EPS, 0));
    ASSERT_TRUE(port_float32_equal(PORT_FLOAT32(1.0), PORT_FLOAT32(1.0) + PORT_FLOAT32_EPS, 1));

#undef TOLERANCE
}

TEST(port_float64_equal)
{
#define TOLERANCE  16

    ASSERT_TRUE(port_float64_equal(PORT_FLOAT64(0.0), PORT_FLOAT64(0.0), TOLERANCE));
    ASSERT_TRUE(port_float64_equal(-TOLERANCE*PORT_FLOAT64_EPS, PORT_FLOAT64(0.0), TOLERANCE));
    ASSERT_TRUE(port_float64_equal(+TOLERANCE*PORT_FLOAT64_EPS, PORT_FLOAT64(0.0), TOLERANCE));
    ASSERT_FALSE(port_float64_equal(-(TOLERANCE+1)*PORT_FLOAT64_EPS, PORT_FLOAT64(0.0), TOLERANCE));
    ASSERT_FALSE(port_float64_equal(+(TOLERANCE+1)*PORT_FLOAT64_EPS, PORT_FLOAT64(0.0), TOLERANCE));
    ASSERT_FALSE(port_float64_equal(PORT_M_NAN, PORT_FLOAT64(0.0), TOLERANCE));
    ASSERT_FALSE(port_float64_equal(PORT_M_INFINITY, PORT_FLOAT64(0.0), TOLERANCE));
    ASSERT_FALSE(port_float64_equal(-PORT_M_INFINITY, PORT_FLOAT64(0.0), TOLERANCE));

    ASSERT_TRUE(port_float64_equal(PORT_FLOAT64(1.0), PORT_FLOAT64(1.0), TOLERANCE));
    ASSERT_TRUE(port_float64_equal(PORT_FLOAT64(1.0)+TOLERANCE*PORT_FLOAT64_EPS, PORT_FLOAT64(1.0), TOLERANCE));
    ASSERT_TRUE(port_float64_equal(PORT_FLOAT64(1.0)-TOLERANCE*PORT_FLOAT64_EPS, PORT_FLOAT64(1.0), TOLERANCE));
    ASSERT_FALSE(port_float64_equal(PORT_FLOAT64(1.0)+(TOLERANCE+1)*PORT_FLOAT64_EPS, PORT_FLOAT64(1.0), TOLERANCE));
    ASSERT_FALSE(port_float64_equal(PORT_FLOAT64(1.0)-(TOLERANCE+1)*PORT_FLOAT64_EPS, PORT_FLOAT64(1.0), TOLERANCE));
    ASSERT_FALSE(port_float64_equal(PORT_M_NAN, PORT_FLOAT64(1.0), TOLERANCE));
    ASSERT_FALSE(port_float64_equal(PORT_M_INFINITY, PORT_FLOAT64(1.0), TOLERANCE));
    ASSERT_FALSE(port_float64_equal(-PORT_M_INFINITY, PORT_FLOAT64(1.0), TOLERANCE));

    ASSERT_TRUE(port_float64_equal(PORT_FLOAT64(768.0), PORT_FLOAT64(768.0), TOLERANCE));
    ASSERT_TRUE(port_float64_equal(PORT_FLOAT64(768.0), PORT_FLOAT64(768.0) + 512*TOLERANCE*PORT_FLOAT64_EPS, TOLERANCE));
    ASSERT_TRUE(port_float64_equal(PORT_FLOAT64(768.0), PORT_FLOAT64(768.0) - 512*TOLERANCE*PORT_FLOAT64_EPS, TOLERANCE));
    ASSERT_FALSE(port_float64_equal(PORT_FLOAT64(768.0), PORT_FLOAT64(768.0) + 512*(TOLERANCE+1)*PORT_FLOAT64_EPS, TOLERANCE));
    ASSERT_FALSE(port_float64_equal(PORT_FLOAT64(768.0), PORT_FLOAT64(768.0) - 512*(TOLERANCE+1)*PORT_FLOAT64_EPS, TOLERANCE));
    ASSERT_FALSE(port_float64_equal(PORT_FLOAT64(768.0), PORT_M_NAN, TOLERANCE));
    ASSERT_FALSE(port_float64_equal(PORT_FLOAT64(768.0), PORT_M_INFINITY, TOLERANCE));
    ASSERT_FALSE(port_float64_equal(PORT_M_NAN, PORT_M_NAN, TOLERANCE));
    ASSERT_TRUE(port_float64_equal(PORT_M_INFINITY, PORT_M_INFINITY, TOLERANCE));
    ASSERT_FALSE(port_float64_equal(-PORT_M_INFINITY, PORT_M_INFINITY, TOLERANCE));
    ASSERT_FALSE(port_float64_equal(PORT_M_NAN, PORT_M_INFINITY, TOLERANCE));

    ASSERT_FALSE(port_float64_equal(PORT_FLOAT64(1.0), PORT_FLOAT64(1.0) + PORT_FLOAT64_EPS, 0));
    ASSERT_TRUE(port_float64_equal(PORT_FLOAT64(1.0), PORT_FLOAT64(1.0) + PORT_FLOAT64_EPS, 1));

#undef TOLERANCE
}

TEST(port_convert_float16_to_float32)
{
    ASSERT_EQ(port_convert_float16_to_float32(0x0000), 0.0f, port_float32_t, "%g");
    ASSERT_EQ(copysign(1.0f, port_convert_float16_to_float32(0x0000)), +1.0f, port_float32_t, "%g");
    ASSERT_EQ(port_convert_float16_to_float32(0x8000), 0.0f, port_float32_t, "%g");
    ASSERT_EQ(copysign(1.0f, port_convert_float16_to_float32(0x8000)), -1.0f, port_float32_t, "%g");

    ASSERT_EQ(port_convert_float16_to_float32(0x0001), 5.9604644775390625e-8f, port_float32_t, "%g");
    ASSERT_EQ(port_convert_float16_to_float32(0x0003), 1.78813934326171875e-7f, port_float32_t, "%g");
    ASSERT_EQ(port_convert_float16_to_float32(0x03FF), 0.000060975551605224609375f, port_float32_t, "%g");
    ASSERT_EQ(port_convert_float16_to_float32(0x0400), 0.00006103515625f, port_float32_t, "%g");
    ASSERT_EQ(port_convert_float16_to_float32(0x3555), 0.33325195f, port_float32_t, "%g");
    ASSERT_EQ(port_convert_float16_to_float32(0x3BFF), 0.99951171875f, port_float32_t, "%g");

    ASSERT_EQ(port_convert_float16_to_float32(0x3C00), +1.0f, port_float32_t, "%g");
    ASSERT_EQ(port_convert_float16_to_float32(0xBC00), -1.0f, port_float32_t, "%g");

    ASSERT_EQ(port_convert_float16_to_float32(0x3C01), 1.0009765625f, port_float32_t, "%g");
    ASSERT_EQ(port_convert_float16_to_float32(0xC000), -2.0f, port_float32_t, "%g");
    ASSERT_EQ(port_convert_float16_to_float32(0x4C18), 16.375f, port_float32_t, "%g");
    ASSERT_EQ(port_convert_float16_to_float32(0x7BFF), 65504.0f, port_float32_t, "%g");

    ASSERT_EQ(port_convert_float16_to_float32(0x7C00), +PORT_M_INFINITY, port_float32_t, "%g");
    ASSERT_EQ(port_convert_float16_to_float32(0xFC00), -PORT_M_INFINITY, port_float32_t, "%g");

    ASSERT_TRUE(isnan(port_convert_float16_to_float32(0x7C01)));
    ASSERT_TRUE(isnan(port_convert_float16_to_float32(0x7E00)));
    ASSERT_TRUE(isnan(port_convert_float16_to_float32(0xFFFF)));
}

TEST(port_convert_float16_to_float32_v2)
{
    port_float32_v2_t vector;

    vector = port_convert_float16_to_float32_v2((port_uint16_v2_t)PORT_V2(0x3C00, 0xBC00));
    ASSERT_EQ(vector.s0, +1.0f, port_float32_t, "%g");
    ASSERT_EQ(vector.s1, -1.0f, port_float32_t, "%g");
}

TEST(port_convert_float16_to_float32_v3)
{
    port_float32_v3_t vector;

    vector = port_convert_float16_to_float32_v3((port_uint16_v3_t)PORT_V3(0x3C00, 0xBC00, 0xC000));
    ASSERT_EQ(vector.s0, +1.0f, port_float32_t, "%g");
    ASSERT_EQ(vector.s1, -1.0f, port_float32_t, "%g");
    ASSERT_EQ(vector.s2, -2.0f, port_float32_t, "%g");
}

TEST(port_convert_float16_to_float32_v4)
{
    port_float32_v4_t vector;

    vector = port_convert_float16_to_float32_v4((port_uint16_v4_t)PORT_V4(0x3C00, 0xBC00, 0xC000, 0x7C00));
    ASSERT_EQ(vector.s0, +1.0f, port_float32_t, "%g");
    ASSERT_EQ(vector.s1, -1.0f, port_float32_t, "%g");
    ASSERT_EQ(vector.s2, -2.0f, port_float32_t, "%g");
    ASSERT_EQ(vector.s3, PORT_M_INFINITY, port_float32_t, "%g");
}

TEST(port_convert_float16_to_float32_v8)
{
    port_float32_v8_t vector;

    vector = port_convert_float16_to_float32_v8((port_uint16_v8_t)PORT_V8(
                0x3C00, 0xBC00, 0xC000, 0x7C00, 0x3555, 0x3BFF, 0x0000, 0x4C18));
    ASSERT_EQ(vector.s0, +1.0f, port_float32_t, "%g");
    ASSERT_EQ(vector.s1, -1.0f, port_float32_t, "%g");
    ASSERT_EQ(vector.s2, -2.0f, port_float32_t, "%g");
    ASSERT_EQ(vector.s3, PORT_M_INFINITY, port_float32_t, "%g");
    ASSERT_EQ(vector.s4, 0.33325195f, port_float32_t, "%g");
    ASSERT_EQ(vector.s5, 0.99951171875f, port_float32_t, "%g");
    ASSERT_EQ(vector.s6, 0.0f, port_float32_t, "%g");
    ASSERT_EQ(vector.s7, 16.375f, port_float32_t, "%g");
}

TEST(port_convert_float16_to_float32_v16)
{
    port_float32_v16_t vector;

    vector = port_convert_float16_to_float32_v16((port_uint16_v16_t)PORT_V16(
                0x3C00, 0xBC00, 0xC000, 0x7C00, 0x3555, 0x3BFF, 0x0000, 0x4C18,
                0x03FF, 0x3C01, 0x7BFF, 0xFBFF, 0x0001, 0x0003, 0xFC00, 0x0400));
    ASSERT_EQ(vector.s0, +1.0f, port_float32_t, "%g");
    ASSERT_EQ(vector.s1, -1.0f, port_float32_t, "%g");
    ASSERT_EQ(vector.s2, -2.0f, port_float32_t, "%g");
    ASSERT_EQ(vector.s3, PORT_M_INFINITY, port_float32_t, "%g");
    ASSERT_EQ(vector.s4, 0.33325195f, port_float32_t, "%g");
    ASSERT_EQ(vector.s5, 0.99951171875f, port_float32_t, "%g");
    ASSERT_EQ(vector.s6, 0.0f, port_float32_t, "%g");
    ASSERT_EQ(vector.s7, 16.375f, port_float32_t, "%g");
    ASSERT_EQ(vector.s8, 0.000060975551605224609375f, port_float32_t, "%g");
    ASSERT_EQ(vector.s9, 1.0009765625f, port_float32_t, "%g");
    ASSERT_EQ(vector.sA, +65504.0f, port_float32_t, "%g");
    ASSERT_EQ(vector.sB, -65504.0f, port_float32_t, "%g");
    ASSERT_EQ(vector.sC, 5.9604644775390625e-8f, port_float32_t, "%g");
    ASSERT_EQ(vector.sD, 1.78813934326171875e-7f, port_float32_t, "%g");
    ASSERT_EQ(vector.sE, -PORT_M_INFINITY, port_float32_t, "%g");
    ASSERT_EQ(vector.sF, 0.00006103515625f, port_float32_t, "%g");
}

TEST(port_convert_float32_to_float16)
{
    ASSERT_EQ(port_convert_float32_to_float16(0.0f), 0x0000, port_uint16_t, "%x");
    ASSERT_EQ(port_convert_float32_to_float16(copysign(0.0f, -1.0f)), 0x8000, port_uint16_t, "%x");

    ASSERT_EQ(port_convert_float32_to_float16(1.0e-8f), 0x0000, port_uint16_t, "%x");
    ASSERT_EQ(port_convert_float32_to_float16(2.9802320611338473099749535322189331055e-8f), 0x0000, port_uint16_t, "%x");
    ASSERT_EQ(port_convert_float32_to_float16(2.98023223876953125e-8f), 0x0000, port_uint16_t, "%x");
    ASSERT_EQ(port_convert_float32_to_float16(2.9802325940408991300500929355621337891e-8f), 0x0001, port_uint16_t, "%x");

    ASSERT_EQ(port_convert_float32_to_float16(5.9604644775390625e-8f), 0x0001, port_uint16_t, "%x");
    ASSERT_EQ(port_convert_float32_to_float16(1.78813934326171875e-7f), 0x0003, port_uint16_t, "%x");
    ASSERT_EQ(port_convert_float32_to_float16(0.000060975551605224609375f), 0x03FF, port_uint16_t, "%x");
    ASSERT_EQ(port_convert_float32_to_float16(0.00006100535028963349759578704833984375f), 0x03FF, port_uint16_t, "%x");

    ASSERT_EQ(port_convert_float32_to_float16(0.0000610053539276123046875f), 0x0400, port_uint16_t, "%x");
    ASSERT_EQ(port_convert_float32_to_float16(0.00006103515625f), 0x0400, port_uint16_t, "%x");
    ASSERT_EQ(port_convert_float32_to_float16(0.33325195f), 0x3555, port_uint16_t, "%x");
    ASSERT_EQ(port_convert_float32_to_float16(0.99951171875f), 0x3BFF, port_uint16_t, "%x");

    ASSERT_EQ(port_convert_float32_to_float16(+1.0f), 0x3C00, port_uint16_t, "%x");
    ASSERT_EQ(port_convert_float32_to_float16(-1.0f), 0xBC00, port_uint16_t, "%x");

    ASSERT_EQ(port_convert_float32_to_float16(1.0009765625f), 0x3C01, port_uint16_t, "%x");
    ASSERT_EQ(port_convert_float32_to_float16(-2.0f), 0xC000, port_uint16_t, "%x");
    ASSERT_EQ(port_convert_float32_to_float16(16.375f), 0x4C18, port_uint16_t, "%x");

    ASSERT_EQ(port_convert_float32_to_float16(65504.0f), 0x7BFF, port_uint16_t, "%x");
    ASSERT_EQ(port_convert_float32_to_float16(65505.0f), 0x7BFF, port_uint16_t, "%x");
    ASSERT_EQ(port_convert_float32_to_float16(65519.99609375f), 0x7BFF, port_uint16_t, "%x");
    ASSERT_EQ(port_convert_float32_to_float16(65520.0f), 0x7C00, port_uint16_t, "%x");

    ASSERT_EQ(port_convert_float32_to_float16(+PORT_M_INFINITY), 0x7C00, port_uint16_t, "%x");
    ASSERT_EQ(port_convert_float32_to_float16(-PORT_M_INFINITY), 0xFC00, port_uint16_t, "%x");

    ASSERT_EQ(port_convert_float32_to_float16(PORT_M_NAN), 0x7E00, port_uint16_t, "%x");
}

TEST(port_convert_float32_to_float16_v2)
{
    port_uint16_v2_t vector;

    vector = port_convert_float32_to_float16_v2((port_float32_v2_t)PORT_V2(+1.0f, -1.0f));
    ASSERT_EQ(vector.s0, 0x3C00, port_uint16_t, "%X");
    ASSERT_EQ(vector.s1, 0xBC00, port_uint16_t, "%X");
}

TEST(port_convert_float32_to_float16_v3)
{
    port_uint16_v3_t vector;

    vector = port_convert_float32_to_float16_v3((port_float32_v3_t)PORT_V3(+1.0f, -1.0f, -2.0f));
    ASSERT_EQ(vector.s0, 0x3C00, port_uint16_t, "%X");
    ASSERT_EQ(vector.s1, 0xBC00, port_uint16_t, "%X");
    ASSERT_EQ(vector.s2, 0xC000, port_uint16_t, "%X");
}

TEST(port_convert_float32_to_float16_v4)
{
    port_uint16_v4_t vector;

    vector = port_convert_float32_to_float16_v4((port_float32_v4_t)PORT_V4(+1.0f, -1.0f, -2.0f, PORT_M_INFINITY));
    ASSERT_EQ(vector.s0, 0x3C00, port_uint16_t, "%X");
    ASSERT_EQ(vector.s1, 0xBC00, port_uint16_t, "%X");
    ASSERT_EQ(vector.s2, 0xC000, port_uint16_t, "%X");
    ASSERT_EQ(vector.s3, 0x7C00, port_uint16_t, "%X");
}

TEST(port_convert_float32_to_float16_v8)
{
    port_uint16_v8_t vector;

    vector = port_convert_float32_to_float16_v8((port_float32_v8_t)PORT_V8(
                +1.0f, -1.0f, -2.0f, PORT_M_INFINITY, 0.33325195f, 0.99951171875f, 0.0f, 16.375f));
    ASSERT_EQ(vector.s0, 0x3C00, port_uint16_t, "%X");
    ASSERT_EQ(vector.s1, 0xBC00, port_uint16_t, "%X");
    ASSERT_EQ(vector.s2, 0xC000, port_uint16_t, "%X");
    ASSERT_EQ(vector.s3, 0x7C00, port_uint16_t, "%X");
    ASSERT_EQ(vector.s4, 0x3555, port_uint16_t, "%X");
    ASSERT_EQ(vector.s5, 0x3BFF, port_uint16_t, "%X");
    ASSERT_EQ(vector.s6, 0x0000, port_uint16_t, "%X");
    ASSERT_EQ(vector.s7, 0x4C18, port_uint16_t, "%X");
}

TEST(port_convert_float32_to_float16_v16)
{
    port_uint16_v16_t vector;

    vector = port_convert_float32_to_float16_v16((port_float32_v16_t)PORT_V16(
                +1.0f, -1.0f, -2.0f, PORT_M_INFINITY, 0.33325195f, 0.99951171875f, 0.0f, 16.375f,
                0.000060975551605224609375f, 1.0009765625f, +65504.0f, -65504.0f,
                5.9604644775390625e-8f, 1.78813934326171875e-7f, -PORT_M_INFINITY, 0.00006103515625f));
    ASSERT_EQ(vector.s0, 0x3C00, port_uint16_t, "%X");
    ASSERT_EQ(vector.s1, 0xBC00, port_uint16_t, "%X");
    ASSERT_EQ(vector.s2, 0xC000, port_uint16_t, "%X");
    ASSERT_EQ(vector.s3, 0x7C00, port_uint16_t, "%X");
    ASSERT_EQ(vector.s4, 0x3555, port_uint16_t, "%X");
    ASSERT_EQ(vector.s5, 0x3BFF, port_uint16_t, "%X");
    ASSERT_EQ(vector.s6, 0x0000, port_uint16_t, "%X");
    ASSERT_EQ(vector.s7, 0x4C18, port_uint16_t, "%X");
    ASSERT_EQ(vector.s8, 0x03FF, port_uint16_t, "%X");
    ASSERT_EQ(vector.s9, 0x3C01, port_uint16_t, "%X");
    ASSERT_EQ(vector.sA, 0x7BFF, port_uint16_t, "%X");
    ASSERT_EQ(vector.sB, 0xFBFF, port_uint16_t, "%X");
    ASSERT_EQ(vector.sC, 0x0001, port_uint16_t, "%X");
    ASSERT_EQ(vector.sD, 0x0003, port_uint16_t, "%X");
    ASSERT_EQ(vector.sE, 0xFC00, port_uint16_t, "%X");
    ASSERT_EQ(vector.sF, 0x0400, port_uint16_t, "%X");
}

