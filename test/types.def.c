#include "test.h"

#include "port/types.typ.h"
#include "port/types.def.h"

TEST(PORT_TYPE_NUM_BITS)
{
    ASSERT_EQ(PORT_TYPE_NUM_BITS(PORT_TYPE_LOGSIZE_QUARTER), 8, port_uint32_t, "%u");
    ASSERT_EQ(PORT_TYPE_NUM_BITS(PORT_TYPE_LOGSIZE_HALF), 16, port_uint32_t, "%u");
    ASSERT_EQ(PORT_TYPE_NUM_BITS(PORT_TYPE_LOGSIZE_SINGLE), 32, port_uint32_t, "%u");
    ASSERT_EQ(PORT_TYPE_NUM_BITS(PORT_TYPE_LOGSIZE_DOUBLE), 64, port_uint32_t, "%u");
}

