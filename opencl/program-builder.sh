#!/bin/sh

cd -- "$(dirname -- "$0")"

: ${CFLAGS:=""}
: ${LFLAGS:=""}

# archipelago/plugin/opencl/scripts/
PREPROCESSOR=preprocess_file.sh program-builder.py \
    --cflags " $CFLAGS" --lflags " -create-library $LFLAGS" \
    --hdrdir "../include" --hdr $(find "../include" -type f -printf '%P\n' | sort) \
    --srcdir "../src" --src $(find "../src" -type f -printf '%P\n' | sort) \
    "$@"

