#include "test.h"

#include "port/cdev/random.fun.h"
#include "port/cdev/random.def.h"
#include "port/cdev/types.def.h"
#include "port/cdev/vector.def.h"

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

TEST(port_random_set_bit_quarter)
{
    {
        port_uint32_t bins[NUM_BINS/2] = {0};

        port_uint32_t rnd = 777;
        for (port_uint32_t i = 0; i < NUM_SAMPLES; i++)
        {
            port_uint8_t bitn = port_random_set_bit_quarter(
                    0x55555555, NULL, &rnd);
            bins[bitn / 2]++;
        }

        port_float_t max_fluctuation = PORT_FLOAT(0.0);
        for (port_uint32_t i = 0; i < NUM_BINS/2; i++)
        {
            port_float_t fluctuation = fabs(bins[i] / ((port_float_t)NUM_SAMPLES/(NUM_BINS/2)) - PORT_FLOAT(1.0));
            if (fluctuation > max_fluctuation)
                max_fluctuation = fluctuation;
        }

        ASSERT_LT(max_fluctuation, PORT_FLOAT(0.02), port_float_t, "%g");
    }

    {
        port_uint32_t bins[NUM_BINS/2] = {0};

        port_uint32_t num_thresholds = NUM_BINS/2 - 1;
        port_memory_unit_t thresholds[(num_thresholds-1)/4+1];

        port_uint8_t step = 1, threshold = 0;
        for (port_uint32_t i = 0; i < num_thresholds; i++)
        {
            thresholds[i/4].as_uint_quarter[i%4] = threshold;
            threshold += step++;
        }

        port_uint32_t rnd = 8888;
        for (port_uint32_t i = 0; i < NUM_SAMPLES; i++)
        {
            port_uint8_t bitn = port_random_set_bit_quarter(0x55555555, thresholds, &rnd);
            bins[bitn / 2]++;
        }

        port_float_t slope;
        {
            port_uint32_t numerator = 0;
            for (port_uint32_t i = 0; i < num_thresholds; i++)
                numerator += bins[i] * i;

            port_uint32_t denominator = 0;
            for (port_uint32_t i = 1; i < num_thresholds; i++)
                denominator += i * i;

            slope = (port_float_t)numerator / denominator;
        }

        port_float_t max_fluctuation = PORT_FLOAT(0.0);
        for (port_uint32_t i = 1; i < num_thresholds; i++)
        {
            port_float_t fluctuation = fabs(bins[i] / (slope*i) - PORT_FLOAT(1.0));
            if (fluctuation > max_fluctuation)
                max_fluctuation = fluctuation;
        }

        ASSERT_LT(max_fluctuation, PORT_FLOAT(0.04), port_float_t, "%f");
    }
}

TEST(port_random_set_bit_half)
{
    {
        port_uint32_t bins[NUM_BINS/2] = {0};

        port_uint32_t rnd = 777;
        for (port_uint32_t i = 0; i < NUM_SAMPLES; i++)
        {
            port_uint8_t bitn = port_random_set_bit_half(
                    0x55555555, NULL, &rnd);
            bins[bitn / 2]++;
        }

        port_float_t max_fluctuation = PORT_FLOAT(0.0);
        for (port_uint32_t i = 0; i < NUM_BINS/2; i++)
        {
            port_float_t fluctuation = fabs(bins[i] / ((port_float_t)NUM_SAMPLES/(NUM_BINS/2)) - PORT_FLOAT(1.0));
            if (fluctuation > max_fluctuation)
                max_fluctuation = fluctuation;
        }

        ASSERT_LT(max_fluctuation, PORT_FLOAT(0.02), port_float_t, "%g");
    }

    {
        port_uint32_t bins[NUM_BINS/2] = {0};

        port_uint32_t num_thresholds = NUM_BINS/2-1;
        port_memory_unit_t thresholds[(num_thresholds-1)/2+1];

        port_uint16_t step = 0, threshold = 0;
        for (port_uint32_t i = 0; i < num_thresholds; i++)
        {
            thresholds[i/2].as_uint_half[i%2] = threshold;
            step += 218; // so that the last bit have almost the same probability as the others within uint16_t
            threshold += step;
        }

        port_uint32_t rnd = 777;
        for (port_uint32_t i = 0; i < NUM_SAMPLES; i++)
        {
            port_uint8_t bitn = port_random_set_bit_half(0x55555555, thresholds, &rnd);
            bins[bitn / 2]++;
        }

        port_float_t slope;
        {
            port_uint32_t numerator = 0;
            for (port_uint32_t i = 0; i < num_thresholds; i++)
                numerator += bins[i] * i;

            port_uint32_t denominator = 0;
            for (port_uint32_t i = 1; i < num_thresholds; i++)
                denominator += i*i;

            slope = (port_float_t)numerator / denominator;
        }

        port_float_t max_fluctuation = PORT_FLOAT(0.0);
        for (port_uint32_t i = 1; i < num_thresholds; i++)
        {
            port_float_t fluctuation = fabs(bins[i] / (slope*i) - PORT_FLOAT(1.0));
            if (fluctuation > max_fluctuation)
                max_fluctuation = fluctuation;
        }

        ASSERT_LT(max_fluctuation, PORT_FLOAT(0.02), port_float_t, "%f");
    }
}

