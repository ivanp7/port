#!/bin/sh

cd -- "$(dirname -- "$0")"

ARCHI_FILE=$1
shift 1

: ${PLATFORM_IDX:="0"}
: ${DEVICE_IDX:="0"}

: ${CFLAGS:=""}
: ${LFLAGS:=""}

: ${OUT_FILE:="port.bin"}

# archipelago/plugin/opencl/scripts/program-builder.py
program-builder.py \
    --file "${ARCHI_FILE}" \
    --plt ${PLATFORM_IDX} --dev ${DEVICE_IDX} \
    --cflags " $CFLAGS" --lflags " -create-library $LFLAGS" \
    --hdrdir "../include" --hdr $(find "../include" -type f -printf '%P\n' | sort) \
    --srcdir "../src" --src $(find "../src" -type f -printf '%P\n' | sort) \
    --out "${OUT_FILE}"

