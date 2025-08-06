#!/bin/sh
set -e

cd -- "$(dirname -- "$0")"

PLATFORM_IDX="$1"
DEVICE_IDX="$2"
shift 2

: ${OUT_FILE:="libport-${PLATFORM_IDX}:${DEVICE_IDX}.bin"}
: ${OUT_DIR:="../build"}

ARCHI_FILE="$(mktemp "build.${OUT_FILE}.archi.XXXX")"
trap 'rm -f "$ARCHI_FILE"' EXIT

./program-builder.sh --platform "$PLATFORM_IDX" --devices "$DEVICE_IDX" --out "$OUT_DIR/$OUT_FILE" > "$ARCHI_FILE"
archi -L -vmax "$ARCHI_FILE"

