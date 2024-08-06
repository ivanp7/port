# A library to aid writing code that is portable between CPU and OpenCL.

This library provides:

* memory model with references that are data-intrinsic alternatives to pointers;
* data storage format that is convenient for the proposed memory model;
* functions for memory allocation/deallocation, mapping/unmapping;
* OpenCL program builder from embedded code;
* portable type definitions for general-purpose scalar and vector types that are the part of OpenCL API;
* portable macro definitions for bit operations;
* portable macro definitions for operations on vector types;
* portable functions and macros for type conversions (including IEEE-754 `float32` <-> `float16`);
* portable constants for math, scalar type limits, language keywords;
* portable pseudorandom number generator;
* other!

## Code organization

The code is split into two domains, `cdev` and `host`.

`cdev` (from 'compute device') is for code that is portable between CPU and OpenCL, i.e.
it can be compiled using conventional compilers like gcc/clang and executed on CPU, but
it can also be fed to OpenCL program building functions and executed on other types of devices such as GPU.
The compute device code requires some amount of care from a programmer not to break the portability.
One must rely on the limited set of features that is available in both C and OpenCL C.
As C23 introduces a lot of changes, the latest C standard OpenCL C is somewhat compatible with is C17.

`host` is for the host (CPU) only, it contains code for initialization and other meta purposes.
There is no restrictions imposed on the host code.

## Memory model

### Memory unit

Memory is addressed using so called units, which are always 32-bit wide.

So, 32-bit wide types are synonymically called `single` types, 64-bit types are called `double` types,
16-bit types are `half` types, and 8-bit types are `quarter` types.

A memory unit is a union:

```c
typedef union port_memory_unit {
    // As unsigned integer
    port_uint_single_t as_uint_single;

    port_uint_half_t as_uint_half[2];
    port_uint_half_v2_t as_uint_half_v2;

    port_uint_quarter_t as_uint_quarter[4];
    port_uint_quarter_v2_t as_uint_quarter_v2[2];
    port_uint_quarter_v4_t as_uint_quarter_v4;

    // As signed integer
    port_sint_single_t as_sint_single;

    port_sint_half_t as_sint_half[2];
    port_sint_half_v2_t as_sint_half_v2;

    port_sint_quarter_t as_sint_quarter[4];
    port_sint_quarter_v2_t as_sint_quarter_v2[2];
    port_sint_quarter_v4_t as_sint_quarter_v4;

    // As floating-point number
    port_float_single_t as_float_single;

    port_uint_half_t as_float_half[2];    // no native float16 type
    port_uint_half_v2_t as_float_half_v2; // use integers instead

    // As memory reference
    port_memory_ref_t as_ref;
    port_memory_ref_half_t as_ref_half[2];
    port_memory_ref_quarter_t as_ref_quarter[4];
} port_memory_unit_t;
```

Pointers to memory are pointers to memory units.

### Memory reference

A memory reference is just a signed integer of single, half, or quarter size.
Meaning of such an integer depends on its sign.

1. When `reference < 0`, it is a 'near' reference. Target pointer is calculated from a base pointer the following way:

```c
target_ptr = base_ptr - reference;
```

2. When `reference >= 0`, it is a 'far' reference. To calculate target pointer, memory table is used.
Several least significant bits of a reference is a table index, the other bits is a shifted offset added to the table pointer:

```c
index_mask = (1 << num_index_bits) - 1;
index = reference & index_mask;
offset = (reference >> num_index_bits) << offset_shift;
target_ptr = memory_table[index] + offset;
```

`memory_table`, `num_index_bits`, and `offset_shift` are specifications of a data structure format.

## How to build

The project is built using the Ninja build system.
A `build.ninja` file is generated using `configure` script.
To see the possible build configuration options, run `configure` without arguments.
To generate `build.ninja`, run `configure <options>`.
To build, run `ninja`.

The configuration script also generates `port.pc` (pkg-config file for `libport`).

## Build dependencies

* gcc-compatible compiler (like clang)
* pkg-config
* ninja

## Dependencies

* OpenCL

* [Station](https://github.com/ivanp7/station) (for applications from `app/`)

## Documentation

Doxygen documentation is available at `docs` subdirectory. To build it, run `make`.

## License

```
   Port is free software: you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Port is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with Port. If not, see <http://www.gnu.org/licenses/>.
```

