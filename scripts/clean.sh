#!/bin/sh
set -e

BUILD_TYPE="$1"

if [ -z "$BUILD_TYPE" ]; then
    sudo rm -rf ./build ./install-test
    exit 0
fi

if [ "$BUILD_TYPE" != "release" ] && [ "$BUILD_TYPE" != "debug" ]; then
    echo "usage: $0 [release|debug]"
    exit 1
fi

BUILD_DIR="build/$BUILD_TYPE"

sudo rm -rf "$BUILD_DIR" ./install-test