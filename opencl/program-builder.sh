#!/bin/sh

cd -- "$(dirname -- "$0")"

ARCHI_FILE=$1
PLATFORM_IDX=$2
DEVICE_IDX=$3
shift 3

: ${CFLAGS:=""}
: ${LFLAGS:=""}

: ${OUT_FILE:="port.${PLATFORM_IDX}.${DEVICE_IDX}.bin"}

# archipelago/plugin/opencl/scripts/program-builder.py
program-builder.py \
    --file "${ARCHI_FILE}" \
    --plt ${PLATFORM_IDX} --dev ${DEVICE_IDX} \
    --cflags " $CFLAGS" --lflags " -create-library $LFLAGS" \
    --hdrdir "../include" --hdr $(find "../include" -type f -printf '%P\n' | sort) \
    --srcdir "../src" --src $(find "../src" -type f -printf '%P\n' | sort) \
    --out "${OUT_FILE}"

