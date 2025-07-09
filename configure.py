#!/usr/bin/env python

# python initialization {{{

import os
import pkgconfig

os.chdir(os.path.dirname(__file__))

# }}}
# project name {{{

PROJECT_NAME = "port"
PROJECT_PREFIX = "port"

# }}}
# names of files/directories {{{

SLIB_NAME = f"lib{PROJECT_PREFIX}.a"
LIB_NAME = f"lib{PROJECT_PREFIX}.so"
EXEC_NAME = f"{PROJECT_PREFIX}"
TESTS_NAME = f"{PROJECT_PREFIX}-tests"


INCLUDE_DIR = "include"
SOURCE_DIR = "src"

TEST_DIR = "test"
TEST_HEADER_FILE = "test.h"
TEST_SOURCE_FILE = "test.c"

BUILD_DIR = "build"

# }}}
# build flags {{{
## common {{{

CFLAGS = ['-march=native', '-pipe', '-std=c17',
          '-Wall', '-Wextra', '-Wpedantic',
          '-Wmissing-prototypes', '-Wstrict-prototypes', '-Wold-style-definition',
          '-Wno-psabi', '-fPIC',
          '-fvisibility=default']
LFLAGS = ['-fPIC', '-Wl,--no-gc-sections']

CFLAGS += [f'-I{INCLUDE_DIR}']

CFLAGS += pkgconfig.cflags('OpenCL').split(' ')
CFLAGS += ['-DCL_TARGET_OPENCL_VERSION=300']

LIBS = []
LIBS += pkgconfig.libs('OpenCL').split(' ')

## }}}
## feature macros {{{

FEATURES = {key: value for key, value in os.environ.items() if key.startswith('FEATURE_')}
CFLAGS += [f'-D{PROJECT_PREFIX.upper()}_{key}{'=' if value else ''}{value}' for key, value in FEATURES.items()]

## }}}
## optimization/profiling {{{

if 'DEBUG' in os.environ:                       ### <<<<<<<<<<<<<<<<<<<< INPUT ENVIRONMENT VARIABLE <<<<<<<<<<<<<<<<<<<<
    CFLAGS += ['-O0', '-g3', '-ggdb3']
else:
    CFLAGS += ['-O2', '-g0', '-U_FORTIFY_SOURCE', '-D_FORTIFY_SOURCE=2']

if 'PROFILE' in os.environ:                     ### <<<<<<<<<<<<<<<<<<<< INPUT ENVIRONMENT VARIABLE <<<<<<<<<<<<<<<<<<<<
    CFLAGS += ['-pg']

## }}}
# }}}
# toolchain {{{

if 'LLVM' in os.environ:                        ### <<<<<<<<<<<<<<<<<<<< INPUT ENVIRONMENT VARIABLE <<<<<<<<<<<<<<<<<<<<
    CC = 'clang'
    CC_FLAGS = ['-fcolor-diagnostics']

    LINKER_STATIC = 'llvm-ar'
    LINKER_STATIC_FLAGS = ['rcs']

    LINKER_EXE = 'clang'
    LINKER_EXE_FLAGS = ['-fuse-ld=lld']
else:
    CC = 'gcc'
    CC_FLAGS = ['-fdiagnostics-color=always']

    LINKER_STATIC = 'gcc-ar'
    LINKER_STATIC_FLAGS = ['rcs']

    LINKER_EXE = 'gcc'
    LINKER_EXE_FLAGS = []

# }}}
# build file generation options {{{

BUILD_LIB = 'NO_LIB' not in os.environ          ### <<<<<<<<<<<<<<<<<<<< INPUT ENVIRONMENT VARIABLE <<<<<<<<<<<<<<<<<<<<
BUILD_TESTS = 'NO_TESTS' not in os.environ      ### <<<<<<<<<<<<<<<<<<<< INPUT ENVIRONMENT VARIABLE <<<<<<<<<<<<<<<<<<<<

# }}}
# utility functions {{{

def source2object(pathname):
    return f"{pathname[:-1]}o"

def collect_sources(path):
    sources = []
    objects = []

    for entry in os.walk(path):
        src = [f'{entry[0]}/{s}' for s in entry[2] if s[-2:] == '.c'] # accept only .c files

        sources += src
        objects += [source2object(f"{BUILD_DIR}/{s}") for s in src] # replace .c extension with .o

    return sources, objects

# }}}
# build.ninja generation {{{

build_ninja_separator = '\n###############################################################################\n'

build_ninja_segments = []
build_ninja_targets = []

## build rules {{{

build_ninja_segments.append(f'''\
CC = {CC}
CC_FLAGS = {' '.join(CC_FLAGS + CFLAGS)}

rule compile
    command = $CC $CC_FLAGS $opts -MMD -MT $out -MF $out.d -c $in -o $out
    description = compile: $out
    depfile = $out.d
    deps = gcc


LINKER_STATIC = {LINKER_STATIC}
LINKER_STATIC_FLAGS = {' '.join(LINKER_STATIC_FLAGS)}

rule link_static
    command = rm -f $out && $LINKER_STATIC $LINKER_STATIC_FLAGS $opts $out $in
    description = link(static): $out


LINKER_EXE = {LINKER_EXE}
LINKER_EXE_FLAGS = {' '.join(LINKER_EXE_FLAGS + LFLAGS)}
LINKER_EXE_FLAGS_LIBS = {' '.join(LIBS)}

rule link_shared
    command = $LINKER_EXE $LINKER_EXE_FLAGS $opts -o $out -Wl,--whole-archive $in -Wl,--no-whole-archive $LINKER_EXE_FLAGS_LIBS -shared -rdynamic
    description = link(shared): $out

rule link_exe
    command = $LINKER_EXE $LINKER_EXE_FLAGS $opts -o $out -Wl,--whole-archive $in -Wl,--no-whole-archive $LINKER_EXE_FLAGS_LIBS
    description = link(executable): $out


rule download
    command = curl -s $url -o $out
    description = download: $out
''')

## }}}
## static library {{{

sources, objects = collect_sources(SOURCE_DIR)

build_ninja_segments.append(f'''\
{'\n'.join([f'build {obj}: compile {src}' for obj, src in zip(objects, sources)])}

build {BUILD_DIR}/{SLIB_NAME}: link_static {' '.join(objects)}
build static_lib: phony {BUILD_DIR}/{SLIB_NAME}
''')
build_ninja_targets.append('static_lib')

## }}}
## shared library {{{

if BUILD_LIB:
    build_ninja_segments.append(f'''\
build {BUILD_DIR}/{LIB_NAME}: link_shared {BUILD_DIR}/{SLIB_NAME}
build lib: phony {BUILD_DIR}/{LIB_NAME}
''')
    build_ninja_targets.append('lib')

## }}}
## tests executable {{{

if BUILD_TESTS:
    header = f"{BUILD_DIR}/{TEST_DIR}/{TEST_HEADER_FILE}"
    source = f"{BUILD_DIR}/{TEST_DIR}/{TEST_SOURCE_FILE}"
    object = source2object(source)

    sources, objects = collect_sources(TEST_DIR)

    build_ninja_segments.append(f'''\
TEST_CODE_URL = "https://gist.githubusercontent.com/ivanp7/506fe8dc053952fd4a960666814cfd9a/raw"

build {header}: download
    url = $TEST_CODE_URL/test.h
build {source}: download
    url = $TEST_CODE_URL/test.c
build {object}: compile {source} || {header}
    opts = -I{BUILD_DIR}/{TEST_DIR}

{'\n'.join([f'build {obj}: compile {src} || {header}\n\
    opts = -I{BUILD_DIR}/{TEST_DIR}' for obj, src in zip(objects, sources)])}

build {BUILD_DIR}/{TESTS_NAME}: link_exe {object} {' '.join(objects)} {BUILD_DIR}/{SLIB_NAME}
build tests: phony {BUILD_DIR}/{TESTS_NAME}
''')
    build_ninja_targets.append('tests')

## }}}
## targets {{{

build_ninja_segments.append(f'''\
build all: phony {' '.join(build_ninja_targets)}
default all
''')

## }}}
## write segments to the file {{{

with open('build.ninja', 'w') as file:
    file.write(f'{build_ninja_separator}\n'.join(build_ninja_segments) + '\n')

## }}}
# }}}

# vim: foldmethod=marker:
