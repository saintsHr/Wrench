#!/bin/sh
set -e

BUILD_TYPE=$(echo "${1:-debug}" | tr '[:lower:]' '[:upper:]')

case "$BUILD_TYPE" in
    DEBUG)
        BUILD_TYPE=Debug
        BUILD_DIR=build/debug
        ;;
    RELEASE)
        BUILD_TYPE=Release
        BUILD_DIR=build/release
        ;;
    *)
        echo "usage: $0 [debug|release]"
        exit 1
        ;;
esac

cmake -B "$BUILD_DIR" -S . -DCMAKE_BUILD_TYPE="$BUILD_TYPE"
cmake --build "$BUILD_DIR" -j$(nproc)