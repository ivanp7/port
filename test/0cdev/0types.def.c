#include <test.h>

#include <port/cdev/types.typ.h>
#include <port/cdev/types.def.h>

TEST(PORT_TYPE_NUM_BITS)
{
    ASSERT_EQ(PORT_TYPE_NUM_BITS(PORT_TYPE_SIZE_QUARTER), 8, port_uint32_t, "%u");
    ASSERT_EQ(PORT_TYPE_NUM_BITS(PORT_TYPE_SIZE_HALF), 16, port_uint32_t, "%u");
    ASSERT_EQ(PORT_TYPE_NUM_BITS(PORT_TYPE_SIZE_SINGLE), 32, port_uint32_t, "%u");
    ASSERT_EQ(PORT_TYPE_NUM_BITS(PORT_TYPE_SIZE_DOUBLE), 64, port_uint32_t, "%u");
}

