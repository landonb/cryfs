#!/bin/bash

# Note: Call this from a cmake build directory (e.g. cmake/) for out-of-source builds
# Examples:
# mkdir cmake && cd cmake && ../run-clang-tidy.sh
# mkdir cmake && cd cmake && ../run-clang-tidy.sh -fix
# mkdir cmake && cd cmake && ../run-clang-tidy.sh -export-fixes fixes.yaml
#
# If this fails with errors in scrypt, you need to run "make" in the build directory and let it run until scrypt is built. Our Makefiles call into theirs, and this is needed to generate some header files.
# Clang-tidy will otherwise complain they're missing.

set -e

NUMCORES=`nproc`

# Run cmake in current working directory, but on source that is in the same directory as this script file
cmake -DBUILD_TESTING=on -DCMAKE_EXPORT_COMPILE_COMMANDS=ON "${0%/*}"

run-clang-tidy.py -j${NUMCORES} -quiet -header-filter "$(realpath ${0%/*})/(src|test)/.*" $@

