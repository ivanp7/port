#include <test.h>

#include <port/cdev/float.fun.h>
#include <port/cdev/constants.def.h>

#include <tgmath.h>

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

TEST(port_convert_float32_to_float16)
{
    ASSERT_EQ(port_convert_float32_to_float16(0.0f), 0x0000, port_uint16_t, "%x");
    ASSERT_EQ(port_convert_float32_to_float16(copysign(0.0f, -1.0f)), 0x8000, port_uint16_t, "%x");

    ASSERT_EQ(port_convert_float32_to_float16(1.0e-8f), 0x0000, port_uint16_t, "%x");
    ASSERT_EQ(port_convert_float32_to_float16(5.9604641222676946199499070644378662109375e-8f), 0x0000, port_uint16_t, "%x");

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

