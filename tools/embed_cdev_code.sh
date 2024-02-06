#!/bin/sh
set -eu
TOOL_DIR="$(dirname -- "$0")"

###############################################################################
# Check availability of required programs
###############################################################################

# needed for the tools
command -v "unifdef" > /dev/null || { echo "'unifdef' program is not available!"; exit 1; }
command -v "xxd" > /dev/null || { echo "'xxd' program is not available!"; exit 1; }

###############################################################################
# Set variables
###############################################################################

: ${IDIR:="include"}
: ${SDIR:="src"}
: ${CDEV_SUBDIR:="cdev"}

: ${VAR_PREFIX:="embedded_cdev"}

GENERATED_SOURCE="$1"
PROJECT_NAME="$2"
ROOT_DIR="$3"
shift 3

###############################################################################
# Prepare list of the headers and sources
###############################################################################

CDEV_HEADERS=$(cd -- "$ROOT_DIR"; find "$IDIR/$PROJECT_NAME/$CDEV_SUBDIR" -type f -name "*.h" | sort)
CDEV_SOURCES=$(cd -- "$ROOT_DIR"; find "$SDIR/$CDEV_SUBDIR" -type f -name "*.c" | sort)

###############################################################################
# Generate the source file with embedded code
###############################################################################

file_var () # convert file path into a source string identifier
{
    echo "$1" | sed "s/[^A-Za-z0-9]/_/g"
}

cat <<  _EOF_ > "$GENERATED_SOURCE"
// This file is generated automatically by $(basename -- "$0")
// Do not edit!

#include <stddef.h>

_EOF_

# embed headers and sources as byte arrays
CDEV_FILES=$(printf "%s\n%s" "$CDEV_HEADERS" "$CDEV_SOURCES")

for file in ${CDEV_FILES}
do
    echo "    embedding '$file'"
    "$TOOL_DIR/preprocess_cdev_file.sh" "$file" "$ROOT_DIR" |
        "$TOOL_DIR/file_to_c_array.sh" "$file" >> "$GENERATED_SOURCE"
    echo >> "$GENERATED_SOURCE"
done

# generate definition of num_headers
cat <<  _EOF_ >> "$GENERATED_SOURCE"

const unsigned int ${VAR_PREFIX}_num_headers = $(echo "$CDEV_HEADERS" | wc -l);

_EOF_

# generate definition of header_include_names
cat <<  _EOF_ >> "$GENERATED_SOURCE"
const char *const ${VAR_PREFIX}_header_include_names[] = {
_EOF_

for file in $CDEV_HEADERS
do
    cat <<  _EOF_ >> "$GENERATED_SOURCE"
    "$(echo "$file" | sed "s@^$IDIR/@@")",
_EOF_
done

cat <<  _EOF_ >> "$GENERATED_SOURCE"
};

_EOF_

# generate definition of headers
cat <<  _EOF_ >> "$GENERATED_SOURCE"
const char *const ${VAR_PREFIX}_headers[] = {
_EOF_

for file in $CDEV_HEADERS
do
    var=$(file_var "$file")

    cat <<  _EOF_ >> "$GENERATED_SOURCE"
    (const char*)${var},
_EOF_
done

cat <<  _EOF_ >> "$GENERATED_SOURCE"
};

_EOF_

# generate definition of header_sizes
cat <<  _EOF_ >> "$GENERATED_SOURCE"
const size_t ${VAR_PREFIX}_header_sizes[] = {
_EOF_

for file in $CDEV_HEADERS
do
    var=$(file_var "$file")

    cat <<  _EOF_ >> "$GENERATED_SOURCE"
    ${var}_len,
_EOF_
done

cat <<  _EOF_ >> "$GENERATED_SOURCE"
};

_EOF_

# generate definition of num_sources
cat <<  _EOF_ >> "$GENERATED_SOURCE"

const unsigned int ${VAR_PREFIX}_num_sources = $(echo "$CDEV_SOURCES" | wc -l);

_EOF_

# generate definition of source_names
cat <<  _EOF_ >> "$GENERATED_SOURCE"
const char *const ${VAR_PREFIX}_source_names[] = {
_EOF_

for file in $CDEV_SOURCES
do
    cat <<  _EOF_ >> "$GENERATED_SOURCE"
    "$(echo "$file" | sed "s@^$SDIR/@@")",
_EOF_
done

cat <<  _EOF_ >> "$GENERATED_SOURCE"
};

_EOF_

# generate definition of sources
cat <<  _EOF_ >> "$GENERATED_SOURCE"
const char *const ${VAR_PREFIX}_sources[] = {
_EOF_

for file in $CDEV_SOURCES
do
    var=$(file_var "$file")

    cat <<  _EOF_ >> "$GENERATED_SOURCE"
    (const char*)${var},
_EOF_
done

cat <<  _EOF_ >> "$GENERATED_SOURCE"
};

_EOF_

# generate definition of source_sizes
cat <<  _EOF_ >> "$GENERATED_SOURCE"
const size_t ${VAR_PREFIX}_source_sizes[] = {
_EOF_

for file in $CDEV_SOURCES
do
    var=$(file_var "$file")

    cat <<  _EOF_ >> "$GENERATED_SOURCE"
    ${var}_len,
_EOF_
done

cat <<  _EOF_ >> "$GENERATED_SOURCE"
};

_EOF_

