#!/bin/sh
set -e

BUILD_TYPE="${1:-release}"

if [ "$BUILD_TYPE" != "release" ] && [ "$BUILD_TYPE" != "debug" ]; then
    echo "usage: $0 [release|debug]"
    exit 1
fi

BUILD_DIR="build/$(echo "$BUILD_TYPE")"

cmake -B "$BUILD_DIR" -S . -DCMAKE_BUILD_TYPE="$BUILD_TYPE"
sudo cmake --install "$BUILD_DIR"