#include "test.h"

#include "port/random.fun.h"
#include "port/types.def.h"
#include "port/vector.def.h"

#include <tgmath.h>

#define BIN_BITS 5
#define NUM_BINS (1 << BIN_BITS)
#define NUM_SAMPLES (1 << 20)

static
port_float_v2_t random_uint32_fluctuation(port_uint32_t *initial)
{
    port_uint32_t bins[NUM_BINS] = {0};
    port_uint32_t bins2[NUM_BINS][NUM_BINS] = {0};

    port_uint32_t prev = *initial, curr;
    for (port_uint32_t i = 0; i < NUM_SAMPLES; i++)
    {
        curr = port_random_uint32(prev);
        bins[curr >> (32 - BIN_BITS)]++;
        bins2[curr >> (32 - BIN_BITS)][prev >> (32 - BIN_BITS)]++;
        prev = curr;
    }
    *initial = curr;

    port_float_t max_fluctuation = PORT_FLOAT(0.0);
    for (port_uint32_t i = 0; i < NUM_BINS; i++)
    {
        port_float_t fluctuation = fabs(bins[i] / ((port_float_t)NUM_SAMPLES/NUM_BINS) - PORT_FLOAT(1.0));
        if (fluctuation > max_fluctuation)
            max_fluctuation = fluctuation;
    }

    port_float_t max_fluctuation2 = PORT_FLOAT(0.0);
    for (port_uint32_t i = 0; i < NUM_BINS; i++)
        for (port_uint32_t j = 0; j < NUM_BINS; j++)
        {
            port_float_t fluctuation = fabs(bins2[i][j] / ((port_float_t)NUM_SAMPLES/NUM_BINS/NUM_BINS) - PORT_FLOAT(1.0));
            if (fluctuation > max_fluctuation2)
                max_fluctuation2 = fluctuation;
        }

    return (port_float_v2_t)PORT_V2(max_fluctuation, max_fluctuation2);
}

TEST(port_random_uint32)
{
    // Sequence of values taken from "Numerical recipies in C. The art of scientific computing"
    port_uint32_t rnd = 0;
    rnd = port_random_uint32(rnd);
    ASSERT_EQ(rnd, 0x3C6EF35Fu, port_uint32_t, "%u");
    rnd = port_random_uint32(rnd);
    ASSERT_EQ(rnd, 0x47502932u, port_uint32_t, "%u");
    rnd = port_random_uint32(rnd);
    ASSERT_EQ(rnd, 0xD1CCF6E9u, port_uint32_t, "%u");
    rnd = port_random_uint32(rnd);
    ASSERT_EQ(rnd, 0xAAF95334u, port_uint32_t, "%u");
    rnd = port_random_uint32(rnd);
    ASSERT_EQ(rnd, 0x6252E503u, port_uint32_t, "%u");
    rnd = port_random_uint32(rnd);
    ASSERT_EQ(rnd, 0x9F2EC686u, port_uint32_t, "%u");
    rnd = port_random_uint32(rnd);
    ASSERT_EQ(rnd, 0x57FE6C2Du, port_uint32_t, "%u");
    rnd = port_random_uint32(rnd);
    ASSERT_EQ(rnd, 0xA3D95FA8u, port_uint32_t, "%u");
    rnd = port_random_uint32(rnd);
    ASSERT_EQ(rnd, 0x81FDBEE7u, port_uint32_t, "%u");
    rnd = port_random_uint32(rnd);
    ASSERT_EQ(rnd, 0x94F0AF1Au, port_uint32_t, "%u");
    rnd = port_random_uint32(rnd);
    ASSERT_EQ(rnd, 0xCBF633B1u, port_uint32_t, "%u");

    for (port_uint32_t i = 0; i < 100; i++)
    {
        port_float_v2_t fluctuation = random_uint32_fluctuation(&rnd);
        ASSERT_LT(fluctuation.s0, PORT_FLOAT(0.02), port_float_t, "%g");
        ASSERT_LT(fluctuation.s1, PORT_FLOAT(0.15), port_float_t, "%g");
    }
}

TEST(port_random_float32)
{
    port_uint32_t rnd = 1337;
    for (port_uint32_t i = 0; i < NUM_SAMPLES; i++)
    {
        port_float32_t value = port_random_float32(&rnd);
        ASSERT_GE(value, 0.0f, port_float32_t, "%g");
        ASSERT_LT(value, 1.0f, port_float32_t, "%g");
    }
}

TEST(port_random_float64)
{
    port_uint32_t rnd = 1337;
    for (port_uint32_t i = 0; i < NUM_SAMPLES; i++)
    {
        port_float64_t value = port_random_float64(&rnd);
        ASSERT_GE(value, 0.0, port_float64_t, "%g");
        ASSERT_LT(value, 1.0, port_float64_t, "%g");
    }
}

TEST(port_random_custom_distrib_uint_quarter)
{
    port_uint32_t rnd = 0;
    port_uint_quarter_t cdf[] = {0, 1, 2, 3, 4, 5};
    port_uint_quarter_t num_outcomes = (sizeof(cdf) / sizeof(cdf[0])) + 1;

    ASSERT_EQ(port_random_custom_distrib_uint_quarter(1, NULL, &rnd), 0, port_uint_quarter_t, "%hhu");
    ASSERT_EQ(port_random_custom_distrib_uint_quarter(1, cdf, &rnd), 0, port_uint_quarter_t, "%hhu");

    rnd = 0;
    ASSERT_EQ(port_random_custom_distrib_uint_quarter(num_outcomes, cdf, &rnd), 1, port_uint_quarter_t, "%hhu");

    rnd = 1;
    ASSERT_EQ(port_random_custom_distrib_uint_quarter(num_outcomes, cdf, &rnd), 2, port_uint_quarter_t, "%hhu");

    rnd = 2;
    ASSERT_EQ(port_random_custom_distrib_uint_quarter(num_outcomes, cdf, &rnd), 3, port_uint_quarter_t, "%hhu");

    rnd = 3;
    ASSERT_EQ(port_random_custom_distrib_uint_quarter(num_outcomes, cdf, &rnd), 4, port_uint_quarter_t, "%hhu");

    rnd = 4;
    ASSERT_EQ(port_random_custom_distrib_uint_quarter(num_outcomes, cdf, &rnd), 5, port_uint_quarter_t, "%hhu");

    rnd = 5;
    ASSERT_EQ(port_random_custom_distrib_uint_quarter(num_outcomes, cdf, &rnd), 6, port_uint_quarter_t, "%hhu");

    rnd = 6;
    ASSERT_EQ(port_random_custom_distrib_uint_quarter(num_outcomes, cdf, &rnd), 6, port_uint_quarter_t, "%hhu");

    rnd = 7;
    ASSERT_EQ(port_random_custom_distrib_uint_quarter(num_outcomes, cdf, &rnd), 6, port_uint_quarter_t, "%hhu");

    cdf[3] = 2;

    rnd = 1;
    ASSERT_EQ(port_random_custom_distrib_uint_quarter(num_outcomes, cdf, &rnd), 2, port_uint_quarter_t, "%hhu");

    rnd = 2;
    ASSERT_EQ(port_random_custom_distrib_uint_quarter(num_outcomes, cdf, &rnd), 4, port_uint_quarter_t, "%hhu");
}

TEST(port_random_custom_distrib_uint_half)
{
    port_uint32_t rnd = 0;
    port_uint_half_t cdf[] = {0, 1, 2, 3, 4, 5};
    port_uint_half_t num_outcomes = (sizeof(cdf) / sizeof(cdf[0])) + 1;

    ASSERT_EQ(port_random_custom_distrib_uint_half(1, NULL, &rnd), 0, port_uint_half_t, "%hu");
    ASSERT_EQ(port_random_custom_distrib_uint_half(1, cdf, &rnd), 0, port_uint_half_t, "%hu");

    rnd = 0;
    ASSERT_EQ(port_random_custom_distrib_uint_half(num_outcomes, cdf, &rnd), 1, port_uint_half_t, "%hu");

    rnd = 1;
    ASSERT_EQ(port_random_custom_distrib_uint_half(num_outcomes, cdf, &rnd), 2, port_uint_half_t, "%hu");

    rnd = 2;
    ASSERT_EQ(port_random_custom_distrib_uint_half(num_outcomes, cdf, &rnd), 3, port_uint_half_t, "%hu");

    rnd = 3;
    ASSERT_EQ(port_random_custom_distrib_uint_half(num_outcomes, cdf, &rnd), 4, port_uint_half_t, "%hu");

    rnd = 4;
    ASSERT_EQ(port_random_custom_distrib_uint_half(num_outcomes, cdf, &rnd), 5, port_uint_half_t, "%hu");

    rnd = 5;
    ASSERT_EQ(port_random_custom_distrib_uint_half(num_outcomes, cdf, &rnd), 6, port_uint_half_t, "%hu");

    rnd = 6;
    ASSERT_EQ(port_random_custom_distrib_uint_half(num_outcomes, cdf, &rnd), 6, port_uint_half_t, "%hu");

    rnd = 7;
    ASSERT_EQ(port_random_custom_distrib_uint_half(num_outcomes, cdf, &rnd), 6, port_uint_half_t, "%hu");

    cdf[3] = 2;

    rnd = 1;
    ASSERT_EQ(port_random_custom_distrib_uint_half(num_outcomes, cdf, &rnd), 2, port_uint_half_t, "%hu");

    rnd = 2;
    ASSERT_EQ(port_random_custom_distrib_uint_half(num_outcomes, cdf, &rnd), 4, port_uint_half_t, "%hu");
}

TEST(port_random_custom_distrib_uint_single)
{
    port_uint32_t rnd = 0;
    port_uint_single_t cdf[] = {0, 1, 2, 3, 4, 5};
    port_uint_single_t num_outcomes = (sizeof(cdf) / sizeof(cdf[0])) + 1;

    ASSERT_EQ(port_random_custom_distrib_uint_single(1, NULL, &rnd), 0, port_uint_single_t, "%u");
    ASSERT_EQ(port_random_custom_distrib_uint_single(1, cdf, &rnd), 0, port_uint_single_t, "%u");

    rnd = 0;
    ASSERT_EQ(port_random_custom_distrib_uint_single(num_outcomes, cdf, &rnd), 1, port_uint_single_t, "%u");

    rnd = 1;
    ASSERT_EQ(port_random_custom_distrib_uint_single(num_outcomes, cdf, &rnd), 2, port_uint_single_t, "%u");

    rnd = 2;
    ASSERT_EQ(port_random_custom_distrib_uint_single(num_outcomes, cdf, &rnd), 3, port_uint_single_t, "%u");

    rnd = 3;
    ASSERT_EQ(port_random_custom_distrib_uint_single(num_outcomes, cdf, &rnd), 4, port_uint_single_t, "%u");

    rnd = 4;
    ASSERT_EQ(port_random_custom_distrib_uint_single(num_outcomes, cdf, &rnd), 5, port_uint_single_t, "%u");

    rnd = 5;
    ASSERT_EQ(port_random_custom_distrib_uint_single(num_outcomes, cdf, &rnd), 6, port_uint_single_t, "%u");

    rnd = 6;
    ASSERT_EQ(port_random_custom_distrib_uint_single(num_outcomes, cdf, &rnd), 6, port_uint_single_t, "%u");

    rnd = 7;
    ASSERT_EQ(port_random_custom_distrib_uint_single(num_outcomes, cdf, &rnd), 6, port_uint_single_t, "%u");

    cdf[3] = 2;

    rnd = 1;
    ASSERT_EQ(port_random_custom_distrib_uint_single(num_outcomes, cdf, &rnd), 2, port_uint_single_t, "%u");

    rnd = 2;
    ASSERT_EQ(port_random_custom_distrib_uint_single(num_outcomes, cdf, &rnd), 4, port_uint_single_t, "%u");
}

